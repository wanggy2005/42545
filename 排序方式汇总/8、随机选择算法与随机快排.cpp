//����������� https://leetcode.cn/problems/sort-an-array/description/?envType=problem-list-v2&envId=Y7h19rjC& O(N*log N)
#define MAXN 100001
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

class QuickSort {
public:
    vector<int> arr; // ���ڴ洢Ҫ���������
    int n; // ����Ĵ�С
    void readInput() { // ��ȡ��������
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }
    }
    void printOutput() {// ��ӡ���������
        for (int i = 0; i < n - 1; i++) {
            cout << arr[i] << " ";
        }
        cout << arr[n - 1] << endl;
    }
    void swap_index(int i, int j) { // ���������е�����Ԫ��
        int tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }
    // ���������������
    void quickSort(int l, int r) {
        if (l >= r) return;
        int x = arr[l + rand() % (r - l + 1)]; // ���ѡ��һ����Ŧֵ ��ֹ���
        /* rand() % (r - l + 1) :��(r - l + 1) ȡģ�������[0, r - l] ֮���һ���������
        l + rand() % (r - l + 1)�õ�[l, r] ֮���һ������±ꡣ*/
        partition(l, r, x); // ���з�������
        int left = first; // ������Ľ���λ��
        int right = last; // �ҷ�������ʼλ��
        quickSort(l, left - 1); // ����������еݹ��������
        quickSort(right + 1, r); // ���ҷ������еݹ��������
    }
private:
    int first, last; // �����ı߽�
    void partition(int l, int r, int x) {// �����������������ΪС�ڡ����ںʹ�����Ŧֵ��������
        first = l; // ��ʼ����߽�
        last = r; // ��ʼ���ұ߽�
        int i = l; // ����߽翪ʼ����
        while (i <= last) { // ������δ�����ұ߽�ʱ
            if (arr[i] == x) {
                i++; // ��ǰԪ�ص�����Ŧֵʱ���ƶ�����һ��Ԫ��
            }
            else if (arr[i] < x) {
                swap_index(first++, i++); // ��ǰԪ��С����Ŧֵ�����������������߽�͵�ǰԪ��ָ��ͬʱ����
            }
            else {
                swap_index(i, last--); // ��ǰԪ�ش�����Ŧֵ���������ұ������ұ߽�����
            }
        }
    }
};
int main() {
    srand(time(0)); // ��ʼ���������
    QuickSort qs(MAXN); // ����QuickSort���󣬳�ʼ�������С
    qs.readInput(); 
    qs.quickSort(0, qs.n - 1); // ������������п�������
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

//�����еĵ�K�����Ԫ�� https://leetcode.cn/problems/kth-largest-element-in-an-array/description/?envType=problem-list-v2&envId=Y7h19rjC&
/*������������ nums ������ k���뷵�������е� k ���Ԫ�ء�
��ע�⣬����Ҫ�ҵ������������ĵ� k ���Ԫ�أ������ǵ� k ����ͬ��Ԫ�ء�
�������Ʋ�ʵ��ʱ�临�Ӷ�Ϊ O(n) ���㷨��������⡣*/
class Solution {
private:
    int first = 0; // ��������ʼλ��
    int last = 0; // �����Ľ���λ��
    void swap(vector<int>& nums, int i, int j) {
        int tmp = nums[j];
        nums[j] = nums[i];
        nums[i] = tmp;
    }
    // �����������������ΪС�ڡ����ںʹ�����Ŧֵ��������
    void partition(vector<int>& nums, int l, int r, int x) {
        first = l;
        last = r;
        int i = l;
        while (i <= last) {
            if (nums[i] == x) {
                i++; // ��ǰԪ�ص�����Ŧֵ������
            }
            else if (nums[i] < x) {
                swap(nums, i++, first++); // ��ǰԪ��С����Ŧֵ������������������ƶ��߽�
            }
            else {
                swap(nums, i, last--); // ��ǰԪ�ش�����Ŧֵ���������ұ��������ƶ��߽�
            }
        }
    }
    // ���ѡ���㷨���ҵ��� index ��Ԫ�أ��� index ���Ԫ�أ�
    int randomizedSelect(vector<int>& nums, int index) {
        int ans = 0;
        for (int l = 0, r = nums.size() - 1; l <= r;) {
            // ���ѡ����Ŧֵ���з���
            partition(nums, l, r, nums[l + rand() % (r - l + 1)]);
            if (index < first) {
                r = first - 1; // �� index ���Ԫ������߷���
            }
            else if (index > last) {
                l = last + 1; // �� index ���Ԫ�����ұ߷���
            }
            else {
                ans = nums[index]; // �ҵ��� index ���Ԫ��
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
