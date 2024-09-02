//1、合并k个有序链表 https://www.nowcoder.com/practice/65cfde9e5b9b4cf2b6bafa5f3ef33fa6
/*合并 k 个升序的链表并将结果作为一个升序的链表返回其头节点。
数据范围：节点总数满足0≤n≤5000，每个节点的val满足∣val∣ <= 1000 要求：时间复杂度O(nlogn)
示例1输入：[{1, 2, 3}, { 4,5,6,7 }]
返回值：{ 1,2,3,4,5,6,7 }
示例2输入：[{1, 2}, { 1,4,5 }, { 6 }]
返回值：{ 1,1,2,4,5,6 } */
#include<vector>
#include<queue>
using namespace std;
struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) : val(x), next(nullptr) {}
};
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        auto cmp=[](ListNode* a,ListNode* b){return a->val>b->val;};
        priority_queue<ListNode*,vector<ListNode*>,decltype(cmp)> heap(cmp);
        for (ListNode* h : lists) {
            if (h != nullptr) {
                heap.push(h);
            }
        }
        ListNode* head = heap.top();
        heap.pop();
        ListNode* pre = head;
        while (!heap.empty()) {
            ListNode* cur = heap.top();
            heap.pop();
            pre->next = cur;
            pre = pre->next;
            if (cur->next != nullptr) {
                heap.push(cur->next);
            }
        }
        return head;
    }
};