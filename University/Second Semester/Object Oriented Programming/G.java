/**
 * PO 2024/25, Problem G - Hacker
 * 2025-04-18 : https://satori.tcs.uj.edu.pl/contest/9753924/problems/9924536
 * @author Hubert Jastrzębski
 */

import sun.misc.Unsafe;

import java.lang.reflect.*;
import java.util.*;
import java.util.function.Function;
import java.util.stream.Collectors;


public class Hacker {
    NewsService newsService;

    public Hacker(NewsService newsService) {
        this.newsService = newsService;
    }

    public String analyzeClass(Class<?> c) {
        Map<String, String> info = classInfo(c);
        return String.format("=== %s Class Analysis ===\n", c.getSimpleName())
                + "Fields:\n" + info.get("fields") + "\n"
                + "Methods:\n" + info.get("methods") + "\n"
                + "Inner Classes:\n" + info.get("innerClasses") + "\n";
    }

    /**
     * Analyzes and returns class structure information as String
     * @return formatted class analysis
     */
    public String analyzeClasses() {
        return analyzeClass(NewsService.class) +
                analyzeClass(User.class) +
                analyzeClass(Tweet.class);
    }

    /**
     * Generates separate strings with information about fields, methods and inner classes
     * * @param clazz class to analyze
     * * @return map with keys: "fields", "methods", "innerClasses" and their corresponding descriptions
     */
    public Map<String, String> classInfo(Class<?> clazz) {
        Map<String, String> info = new HashMap<>();

        StringBuilder sb_fields = new StringBuilder();
        for (Field f : clazz.getDeclaredFields())
            sb_fields.append(String.format("- %s %s (modifiers: %s)\n", f.getType().getSimpleName(), f.getName(),
                    Modifier.toString(f.getModifiers())));
        info.put("fields", sb_fields.toString());

        StringBuilder sb_methods = new StringBuilder();
        for (Method m : clazz.getDeclaredMethods())
            sb_methods.append(String.format("- %s %s(%s) (modifiers: %s)\n", m.getReturnType().getSimpleName(), m.getName(),
                    Arrays.stream(m.getParameterTypes()).map(Class::getSimpleName).collect(Collectors.joining(", ")),
                    Modifier.toString(m.getModifiers())));
        info.put("methods", sb_methods.toString());

        StringBuilder sb_innerClasses = new StringBuilder();
        for (Class<?> ic : clazz.getDeclaredClasses())
            sb_innerClasses.append(String.format("- %s (modifiers: %s)\n", ic.getSimpleName(), Modifier.toString(ic.getModifiers())));
        info.put("innerClasses", sb_innerClasses.toString());

        return info;
    }

    /**
     * Gets the registered users map through reflection
     * @return map of username to User objects
     */
    @SuppressWarnings("unchecked")
    public Map<String, User> getUsersMap() throws Exception {
        Field users = NewsService.class.getDeclaredField("users");
        users.setAccessible(true);
        return (Map<String, User>) users.get(this.newsService);
    }

    /**
     * Gets the currently logged in user through reflection
     */
    public User getLoggedInUser() throws Exception {
        Field loggedInUser = NewsService.class.getDeclaredField("loggedInUser");
        loggedInUser.setAccessible(true);
        return (User) loggedInUser.get(this.newsService);
    }

    /**
     * Creates a user without invoking the constructor
     * @return newly created user
     */
    public User createUserWithoutConstructor(String username, String password, String role) throws Exception {
        Field f = Unsafe.class.getDeclaredField("theUnsafe");
        f.setAccessible(true);
        Unsafe unsafe = (Unsafe) f.get(null);
        User user = (User) unsafe.allocateInstance(User.class);

        Field usernameField = User.class.getDeclaredField("username");
        usernameField.setAccessible(true);
        usernameField.set(user, username);

        Field passwordField = User.class.getDeclaredField("password");
        passwordField.setAccessible(true);
        passwordField.set(user, password);

        Field roleField = User.class.getDeclaredField("role");
        roleField.setAccessible(true);
        roleField.set(user, role);

        return user;
    }

    /**
     * Changes a user's role through reflection
     */
    public void changeUserRole(User user, String newRole) throws Exception {
        Field role = User.class.getDeclaredField("role");
        role.setAccessible(true);
        role.set(user, newRole);
    }

    /**
     * Impersonates another user by modifying loggedInUser
     */
    public void impersonateUser(String username) throws Exception {
        Field loggedInUser = NewsService.class.getDeclaredField("loggedInUser");
        loggedInUser.setAccessible(true);
        Map<String, User> users = getUsersMap();
        loggedInUser.set(this.newsService, users.get(username));
    }

    /**
     * Modifies all tweets of logged in user
     */
    public void modifyTweetsList() throws Exception {
        User user = getLoggedInUser();

        Field tweets = User.class.getDeclaredField("tweets");
        tweets.setAccessible(true);
        Field content = Tweet.class.getDeclaredField("content");
        content.setAccessible(true);
        Field timestamp = Tweet.class.getDeclaredField("timestamp");
        timestamp.setAccessible(true);

        List<?> tweetsList = (List<?>) tweets.get(user);
        List<Tweet> hackedTweets = new ArrayList<>();
        for (Object tweetObj : tweetsList) {
            Tweet tweet = (Tweet) tweetObj;
            Tweet hackedTweet = new Tweet("[HACKED] " + content.get(tweet), (Date)timestamp.get(tweet));
            hackedTweets.add(hackedTweet);
        }

        tweets.set(user, hackedTweets);
    }

    /**
     * Creates a backdoor admin account
     */
    public void createBackdoorAdmin() throws Exception {
        addUserViaAdminTools(createUserWithoutConstructor("backdoor_admin", "admin", "admin"));
    }

    /**
     * Overrides authorization
     */
    public void overrideAuthorizationCheck() throws Exception {
        Field authorizationCheck = NewsService.class.getDeclaredField("authorizationCheck");
        authorizationCheck.setAccessible(true);
        authorizationCheck.set(this.newsService, (Function<String, Boolean>) x -> true);
    }

    // Helper methods

    /**
     * Adds a user to the special access list through AdminTools
     */
    public void addUserViaAdminTools(User user) throws Exception {
        Map<String, User> usersMap = getUsersMap();
        usersMap.put(user.getUsername(), user);

        Class<?> adminToolsClass = NewsService.class.getDeclaredClasses()[0];
        Constructor<?> adminToolsConstructor = adminToolsClass.getDeclaredConstructor();
        adminToolsConstructor.setAccessible(true);
        Object adminToolsInstance = adminToolsConstructor.newInstance();

        Method grantSpecialAccess = adminToolsClass.getDeclaredMethod("grantSpecialAccess", User.class);
        grantSpecialAccess.setAccessible(true);
        grantSpecialAccess.invoke(adminToolsInstance, user);
    }
}