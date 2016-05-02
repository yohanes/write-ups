# Can you repo it? (5 pts)

This is just a recon challenge. Searching for "git" in the illintentions.apk, I found:

```
res/values/strings.xml:    <string name="git_user">l33tdev42</string>
```

Going to the github: https://github.com/l33tdev42/

We can see the only app there, and we can see the [latest commit](https://github.com/l33tdev42/testApp/commit/5b315cbbfaa2da9502ffae73f283d36d89f92194) containing the flag:

```
-            keyPassword = "ctf{TheHairCutTookALoadOffMyMind}"
```
