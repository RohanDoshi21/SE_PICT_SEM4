import java.util.Scanner;

public class Assignment9 {

    public static void heapsort(int arr[]) {
        int n = arr.length;

        // Build heap
        for (int i = n / 2 - 1; i >= 0; i--)
            heapify(arr, n, i);

        // Heap Sort
        for (int i = n - 1; i > 0; i--) {
            // after each iteration largest element present at start
            int temp = arr[0];
            arr[0] = arr[i];
            arr[i] = temp;

            heapify(arr, i, 0);
        }
    }

    static void heapify(int arr[], int n, int i) {
        int largest = i; // largest is root
        int l = 2 * i + 1;
        int r = 2 * i + 2;

        // left greater than root and also not overflow
        if (l < n && arr[l] > arr[largest]) largest = l;

        // right greater than root and also not overflow
        if (r < n && arr[r] > arr[largest]) largest = r;

        // If largest is not root
        if (largest != i) {
            int swap = arr[i];
            arr[i] = arr[largest];
            arr[largest] = swap;

            // heap sort the subtree
            heapify(arr, n, largest);
        }
    }

    public static void main(String[] args) {
        System.out.print("Enter the number of elements: ");
        Scanner sc = new Scanner(System.in);
        int length = sc.nextInt();

        int arr[] = new int[length];

        for (int i = 0; i < length; i++) {
            arr[i] = sc.nextInt();
        }

        heapsort(arr);

        System.out.println("Heap Sort: ");
        for (int i = 0; i < length; i++) {
            System.out.print(arr[i] + " ");
        }

        System.out.println();
    }
}