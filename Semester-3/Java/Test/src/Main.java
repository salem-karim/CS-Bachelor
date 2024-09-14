//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {
    public static String getHello() {
        return Hello;
    }
    private static final String Hello = "Hello World!";
    public static void main(String[] args) {
        System.out.println("Hello and welcome!");
        System.out.println(getHello());

        for (int i = 1; i <= 5; i++) {
            System.out.println("i = " + i);
        }
    }
}