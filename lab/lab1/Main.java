import java.util.Scanner;
class Node {
    int num;
    Node next;
    public Node(int num) {
        this.num = num;
        this.next = null;
    }
}

public class Main {
    Node head;
    // 初始化
    public Main() {
        head = new Node(0);  // 头节点，不存储有效值
        head.next = null;
    }
    // 添加到最后
    public void addLast(int num) {
        Node p = head;
        Node newNode = new Node(num);

        while (p.next != null) {
            p = p.next;
        }
        p.next = newNode;
    }

    // 添加到值为indexNum的节点后面
    public void addIndex(int num, int indexNum) {
        Node p = head.next;
        Node newNode = new Node(num);

        while (p.next != null && p.num != indexNum) {
            p = p.next;
        }
        // 如果找到匹配的节点
        newNode.next = p.next;
        p.next = newNode;
    }

    // 删除值为indexNum的节点
    public void deleteIndex(int indexNum) {
        Node p = head;

        while (p.next != null && p.next.num != indexNum) {
            p = p.next;
        }
        if (p.next != null) {  // 如果找到匹配的节点
            p.next = p.next.next;

        }
    }

    // 打印链表
    public void printLinkList() {
        Node p = head.next;
        if (p == null) {
            System.out.println("None");
        } else {
            while (p != null) {
                System.out.print(p.num + " ");
                p = p.next;
            }
            System.out.println();
        }
    }

    public static void main(String[] args){
        Main L = new Main();
        Scanner scanner = new Scanner(System.in);
        boolean panduan = false;
        // 处理操作命令
        while (scanner.hasNextLine() ) {
            if(!panduan) {
                panduan = true;
                String input = scanner.nextLine().trim();
                String[] tokens = input.split(" ");
                for(String i:tokens) {
                    L.addLast(Integer.parseInt(i));
                }
            }
            String input = scanner.nextLine().trim();  // 去掉前后的空白
            if (input.isEmpty()) {
                break;
            }
            String[] tokens = input.split(" ");  // 按空格拆分命令
            if (tokens[0].equals("add")) {
                int indexNum = Integer.parseInt(tokens[1]);
                int num = Integer.parseInt(tokens[2]);
                L.addIndex(num, indexNum);
            } else if (tokens[0].equals("delete")) {
                int indexNum = Integer.parseInt(tokens[1]);
                L.deleteIndex(indexNum);
            }
        }
        L.printLinkList();
        scanner.close();
    }
}