//随机快速排序 https://leetcode.cn/problems/sort-an-array/description/?envType=problem-list-v2&envId=Y7h19rjC& O(N*log N)
#define MAXN 100001
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

class QuickSort {
public:
    vector<int> arr; // 用于存储要排序的数组
    int n; // 数组的大小
    void readInput() { // 读取输入数据
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }
    }
    void printOutput() {// 打印排序后的输出
        for (int i = 0; i < n - 1; i++) {
            cout << arr[i] << " ";
        }
        cout << arr[n - 1] << endl;
    }
    void swap_index(int i, int j) { // 交换数组中的两个元素
        int tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }
    // 快速排序的主函数
    void quickSort(int l, int r) {
        if (l >= r) return;
        int x = arr[l + rand() % (r - l + 1)]; // 随机选择一个枢纽值 防止溢出
        /* rand() % (r - l + 1) :对(r - l + 1) 取模，结果是[0, r - l] 之间的一个随机数。
        l + rand() % (r - l + 1)得到[l, r] 之间的一个随机下标。*/
        partition(l, r, x); // 进行分区操作
        int left = first; // 左分区的结束位置
        int right = last; // 右分区的起始位置
        quickSort(l, left - 1); // 对左分区进行递归快速排序
        quickSort(right + 1, r); // 对右分区进行递归快速排序
    }
private:
    int first, last; // 分区的边界
    void partition(int l, int r, int x) {// 分区函数，将数组分为小于、等于和大于枢纽值的三部分
        first = l; // 初始化左边界
        last = r; // 初始化右边界
        int i = l; // 从左边界开始遍历
        while (i <= last) { // 当遍历未超出右边界时
            if (arr[i] == x) {
                i++; // 当前元素等于枢纽值时，移动到下一个元素
            }
            else if (arr[i] < x) {
                swap_index(first++, i++); // 当前元素小于枢纽值，交换到左边区，左边界和当前元素指针同时右移
            }
            else {
                swap_index(i, last--); // 当前元素大于枢纽值，交换到右边区，右边界左移
            }
        }
    }
};
int main() {
    srand(time(0)); // 初始化随机种子
    QuickSort qs(MAXN); // 创建QuickSort对象，初始化数组大小
    qs.readInput(); 
    qs.quickSort(0, qs.n - 1); // 对整个数组进行快速排序
    qs.printOutput();
    return 0;
}

class Solution {
private:
    void quickSort(vector<int>& nums, int l, int r) {
        if (l >= r) return;
        int left, right;
        int x = nums[l + rand() % (r - l + 1)];
        partition(nums, l, x, r, left, right);
        quickSort(nums, l, left - 1);
        quickSort(nums, right + 1, r);
    }
    void partition(vector<int>& nums, int l, int x, int r, int& left, int& right) {
        int first = l;
        int last = r;
        int i = l;
        while (i <= last) {
            if (nums[i] == x) {
                i++;
            }
            else if (nums[i] < x) {
                swap_index(nums, first++, i++);
            }
            else {
                swap_index(nums, i, last--);
            }
        }
        left = first;
        right = last;
    }
    void swap_index(vector<int>& arr, int i, int j) {
        int tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }
public:
    vector<int> sortArray(vector<int>& nums) {
        quickSort(nums, 0, nums.size() - 1);
        return nums;
    }
};

//数组中的第K个最大元素 https://leetcode.cn/problems/kth-largest-element-in-an-array/description/?envType=problem-list-v2&envId=Y7h19rjC&
/*给定整数数组 nums 和整数 k，请返回数组中第 k 大的元素。
请注意，你需要找的是数组排序后的第 k 大的元素，而不是第 k 个不同的元素。
你必须设计并实现时间复杂度为 O(n) 的算法解决此问题。*/
class Solution {
private:
    int first = 0; // 分区的起始位置
    int last = 0; // 分区的结束位置
    void swap(vector<int>& nums, int i, int j) {
        int tmp = nums[j];
        nums[j] = nums[i];
        nums[i] = tmp;
    }
    // 分区函数，将数组分为小于、等于和大于枢纽值的三部分
    void partition(vector<int>& nums, int l, int r, int x) {
        first = l;
        last = r;
        int i = l;
        while (i <= last) {
            if (nums[i] == x) {
                i++; // 当前元素等于枢纽值，跳过
            }
            else if (nums[i] < x) {
                swap(nums, i++, first++); // 当前元素小于枢纽值，交换到左边区，并移动边界
            }
            else {
                swap(nums, i, last--); // 当前元素大于枢纽值，交换到右边区，并移动边界
            }
        }
    }
    // 随机选择算法，找到第 index 个元素（第 index 大的元素）
    int randomizedSelect(vector<int>& nums, int index) {
        int ans = 0;
        for (int l = 0, r = nums.size() - 1; l <= r;) {
            // 随机选择枢纽值进行分区
            partition(nums, l, r, nums[l + rand() % (r - l + 1)]);
            if (index < first) {
                r = first - 1; // 第 index 大的元素在左边分区
            }
            else if (index > last) {
                l = last + 1; // 第 index 大的元素在右边分区
            }
            else {
                ans = nums[index]; // 找到第 index 大的元素
                break;
            }
        }
        return ans;
    }
public:
    int findKthLargest(vector<int>& nums, int k) {
        return randomizedSelect(nums, nums.size() - k);
    }
};

class Solution {
private:
    void swap(vector<int>& nums, int i, int j) {
        int tmp = nums[i];
        nums[i] = nums[j];
        nums[j] = tmp;
    }
    void quickSort(vector<int>& nums, int l, int r) {
        if (l >= r)    return;
        int x = nums[l + rand() % (r - l + 1)];
        int left, right;
        partition(nums, l, r, x, left, right);
        quickSort(nums, l, left - 1);
        quickSort(nums, right + 1, r);
    }
    void partition(vector<int>& nums, int l, int r, int x, int& left, int& right) {
        int first = l;
        int last = r;
        int i = l;
        while (i <= last) {
            if (nums[i] == x) {
                i++;
            }
            else if (nums[i] > x) {
                swap(nums, i, last--);
            }
            else { // nums[i] < x
                swap(nums, i++, first++);
            }
        }
        left = first;
        right = last;
    }
public:
    int findKthLargest(vector<int>& nums, int k) {
        quickSort(nums, 0, nums.size() - 1);
        return nums[nums.size() - k];
    }
};
