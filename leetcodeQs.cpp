#include<iostream>
#include<vector>
#include<stack>
#include<string>
#include<memory>
#include<algorithm>
#include<functional>
#include<queue>
#include <stdio.h>
#include<string>
#include<sstream>
#include<istream>
#include <thread>        
#include <mutex>
#include <map>
#include <unordered_map>
#include<unordered_set>
using namespace std;










































struct DLinkedNode {
	int key, value;
	DLinkedNode* prev;
	DLinkedNode* next;
	DLinkedNode():key(0),value(0),prev(nullptr),next(nullptr){}
	DLinkedNode(int _key, int _value): key(_key),value(_value),prev(nullptr),next(nullptr){}
};
class LRUCache {
private:
	unordered_map<int, DLinkedNode*> cache;
	DLinkedNode* head;
	DLinkedNode* tail;
	int size;
	int capacity;
public:
	LRUCache(int _capacity) :capacity(_capacity), size(0) {
		head = new DLinkedNode();
		tail = new DLinkedNode();
		head->next = tail;
		tail->prev = head;
	}
	void addToHead(DLinkedNode* node) {
		node->prev = head;
		node->next = head->next;
		head->next->prev = node;
		head->next = node;
	}
	void removeNode(DLinkedNode* node) {
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}
	void moveToHead(DLinkedNode* node) {
		removeNode(node);
		addToHead(node);
	}
	DLinkedNode* removeTail() {
		DLinkedNode* node = tail->prev;
		removeNode(node);
		return node;
	}
	int get(int key) {
		if (!cache.count(key)) {
			return -1;
		}
		DLinkedNode* node = cache[key];
		moveToHead(node);
		return node->value;
	}
	void put(int key, int value) {
		if (!cache.count(key)) {
			DLinkedNode* node = new DLinkedNode(key, value);
			cache[key] = node;
			addToHead(node);
			++size;
			if (size > capacity) {
				DLinkedNode* removed = removeTail();
				cache.erase(removed->key);
				delete removed;
				--size;
			}
		}
		else {
			DLinkedNode* node = cache[key];
			node->value = value;
			moveToHead(node);
		}
	}
};
class course {
public:
	string name;
	int section;
	int credits;
	course() {}
	course(string n, int s, int c) : name(n), section(s), credits(c) {}
	
};


class Node          //组成双向链表的节点
{
public:
	int data;
	Node* pNext;
	Node* pLast;
};

class List      //构造一个双向链表
{
private:
	Node* pHead;
	Node* pTail;
	int length;
public:
	List(int length)
	{
		this->length = length;
		pHead = new Node();
		pHead->pLast = NULL;
		pTail = pHead;
		for (int i = 0; i < length; i++)
		{
			Node* temp = new Node();
			cout << "please enter the no" << i + 1 << " Node's data:";
			cin >> temp->data;
			temp->pNext = NULL;
			temp->pLast = pTail;
			pTail->pNext = temp;
			pTail = temp;
		}
	}

	void traverseList()
	{
		Node* p = pHead->pNext;
		while (p != NULL)
		{
			cout << p->data << endl;
			p = p->pNext;
		}
	}

	void traverseListReturn()
	{
		Node* p = pTail;
		while (p->pLast != NULL)
		{
			cout << p->data << endl;
			p = p->pLast;
		}
	}

	void sortList()
	{
		Node* p = new Node();
		Node* q = new Node();
		int temp;
		for (p = pHead->pNext; p->pNext != NULL; p = p->pNext)
		{
			for (q = p->pNext; q != NULL; q = q->pNext)
			{
				if (q->data < p->data)
				{
					temp = q->data;
					q->data = p->data;
					p->data = temp;
				}
			}
		}
	}

	void sortListByInsertWay()
	{
		if (pHead->pNext == NULL || pHead->pNext->pNext == NULL)
		{
			return;
		}
		Node* p2 = pHead->pNext->pNext;
		Node* p1 = pHead;
		pHead->pNext->pNext = NULL;
		while (p2)
		{
			Node* pN = p2->pNext;
			while (p1->pNext)
			{
				if (p2->data < p1->pNext->data)
				{
					p2->pNext = p1->pNext;
					p2->pLast = p1;
					p1->pNext->pLast = p2;
					p1->pNext = p2;
					break;
				}
				p1 = p1->pNext;
			}
			if (p1->pNext == NULL)
			{
				p2->pNext = NULL;
				p2->pLast = p1;
				p1->pNext = p2;
			}
			p2 = pN;
		}

		//重新查找pTail的位置
		Node* pt = pHead;
		while (pt->pNext)
		{
			pt = pt->pNext;
		}
		pTail = pt;
	}

	void changeList(int num, int position)
	{
		Node* p = pHead->pNext;
		if (position > length || position <= 0)
		{
			cout << "over stack !" << endl;
			return;
		}
		for (int i = 0; i < position - 1; i++)
		{
			p = p->pNext;
		}
		p->data = num;
	}

	void insertList(int num, int position)
	{
		Node* p = pHead->pNext;
		if (position > length || position <= 0)
		{
			cout << "over stack !" << endl;
			return;
		}
		for (int i = 0; i < position - 1; i++)
		{
			p = p->pNext;
		}
		Node* temp = new Node();
		temp->data = num;
		temp->pNext = p;
		temp->pLast = p->pLast;
		p->pLast->pNext = temp;
		p->pLast = temp;
		length++;
	}

	void clearList()
	{
		Node* q;
		Node* p = pHead->pNext;
		while (p != NULL)
		{
			q = p;
			p = p->pNext;
			delete q;
		}
		p = NULL;
		q = NULL;
	}

	void deleteList(int position)
	{
		Node* p = pHead->pNext;
		if (position > length || position <= 0)
		{
			cout << "over stack !" << endl;
			return;
		}
		for (int i = 0; i < position - 1; i++)
		{
			p = p->pNext;
		}
		p->pLast->pNext = p->pNext;
		p->pNext->pLast = p->pLast;
		delete p;
		length--;
	}

	int getItemInList(int position)
	{
		Node* p = pHead->pNext;
		if (position > length || position <= 0)
		{
			cout << "over stack !" << endl;
			return 0;
		}
		for (int i = 0; i < position - 1; i++)
		{
			p = p->pNext;
		}
		return p->data;
	}

	~List()
	{
		Node* q;
		Node* p = pHead->pNext;
		while (p != NULL)
		{
			q = p;
			p = p->pNext;
			delete q;
		}
		p = NULL;
		q = NULL;
	}

};



struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x): val(x),left(nullptr),right(nullptr){}
	TreeNode() : left(nullptr), right(nullptr) {}
};
struct ListNode
{
	int val;
	ListNode* next;
	ListNode(int x): val(x), next(nullptr){}
	ListNode(): next(nullptr){}
};
class SinglyLinkedList {
public:
	ListNode* head;
	SinglyLinkedList() : head(nullptr) {}
	SinglyLinkedList(const initializer_list<int>& I);


};
SinglyLinkedList::SinglyLinkedList(const initializer_list<int>& I) {
	head = nullptr;
	auto p1{ I.end() - 1 };
	while (p1 != I.begin() - 1) {
		ListNode* p2 = new ListNode(*p1);
		p2->next = head;
		head = p2;
		p1 = p1 - 1;
	}
}
//Binary tree
class preorder {
public:
	vector<int> preorder_iterative(TreeNode* root) {
		stack<TreeNode*> st;
		vector<int> result;
		st.push(root);
		while (!st.empty()) {
			TreeNode* tmp = st.top();
			st.pop();
			result.push_back(tmp->val);
			if(tmp->right!=nullptr) st.push(tmp->right);
			if (tmp->left != nullptr)st.push(tmp->left);
		}
		return result;
	}
	void traversal(TreeNode* cur, vector<int>& vec) {
		if (cur == nullptr) return;
		vec.push_back(cur->val);
		traversal(cur->left, vec);
		traversal(cur->right, vec);
	}
	vector<int> preorderTraversal(TreeNode* root) {
		vector<int> result;
		traversal(root, result);
		return result;
	}
};
class inorder {
public:
	vector<int> inorder_iterative(TreeNode* root) {
		stack<TreeNode*> st;
		vector<int> res;
		TreeNode* cur = root;
		while (cur != nullptr || !st.empty()) {
			if (cur != nullptr) {
				st.push(cur);
				cur = cur->left;
			}

			else {
				cur = st.top();
				st.pop();
				res.push_back(cur->val);
				cur = cur->right;
			}
		}
		return res;
	}  
};
class postorder {
public:
	vector<int> postorder_iterative(TreeNode* root) {
		stack<TreeNode*> st;
		vector<int> result;
		st.push(root);
		while (!st.empty()) {
			TreeNode* tmp = st.top();
			st.pop();
			result.push_back(tmp->val);
			if (tmp->left != nullptr)st.push(tmp->left);
			if (tmp->right != nullptr) st.push(tmp->right);
		}
		reverse(result.begin(), result.end());
		return result;
	}
};
class levelorder {
public:
	vector<vector<int>> LevelOrder(TreeNode* root) {
		queue<TreeNode*> que;
		if (root != nullptr) que.push(root);
		vector<vector<int>> res;
		while (!que.empty()) {
			int size = que.size();
			vector<int> vec;
			for (int i = 0; i < size; i++) {
				TreeNode* tmp = que.front();
				que.pop();
				vec.push_back(tmp->val);
				if (tmp->left != nullptr) que.push(tmp->left);
				if (tmp->right != nullptr) que.push(tmp->right);
			}
			res.push_back(vec);
		}
		return res;
	}
};
class zlevelorder {
public:
	vector<vector<int>> zlevel(TreeNode* root) {
		vector<vector<int>> res;
		if (root == nullptr) return res;
		bool flag = true;
		deque<TreeNode*> q;
		q.push_back(root);
		while (!q.empty()) {
			int n = q.size();
			vector<int> out;
			TreeNode* node;
			while (n > 0) {
				if (flag) {
					node = q.front();
					q.pop_front();
					if (node->left) {
						q.push_back(node->left);
					}
					if (node->right) {
						q.push_back(node->right);
					}
				}
				else {
					node = q.back();
					q.pop_back();
					if (node->right) {
						q.push_back(node->right);
					}
					if (node->left) {
						q.push_back(node->left);
					}
				}
					out.push_back(node->val);
					n--;
			}
				flag = !flag;
				res.push_back(out);
			
		}
		return res;
	}
};
class sametree {
public:
	bool isSameTree(TreeNode* p, TreeNode* q) {
		if (p == nullptr && q == nullptr) {
			return true;
		}
		else if (p == nullptr || q == nullptr) {
			return false;
		}
		else if (p->val != q->val) {
			return false;
		}
		else {
			return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
		}
	}
};
class InvertTree {
public:
	TreeNode* invertTree(TreeNode* root) {
		queue<TreeNode*> que;
		if (root != nullptr) que.push(root);
		while (!que.empty()) {
			int size = que.size();
			for (int i = 0; i < size; i++) {
				TreeNode* node = que.front();
				que.pop();
				swap(node->left, node->right);
				if (node->left)que.push(node->left);
				if (node->right)que.push(node->right);
			}
		}
		return root;
	}
};
class RightSide {
public:
	vector<int> rightSideView(TreeNode* root) {
		queue<TreeNode*> que;
		if (root != nullptr) que.push(root);
		vector<int> result;
		while (!que.empty()) {
			int size = que.size();
			for (int i = 0; i < size; i++) {
				TreeNode* node = que.front();
				que.pop();
				if (i == (size - 1))result.push_back(node->val);
				if (node->left)que.push(node->left);
				if (node->right)que.push(node->right);

			}
		}
		return result;
	}

};
class GetDepth {
public:
	int getdepth(TreeNode* node) {
		if (node == nullptr) {
			return 0;
		}
		int leftdepth = getdepth(node->left);
		int rightdepth = getdepth(node->right);
		int depth = 1 + max(leftdepth, rightdepth);
		return depth;
	}
	int maxdepth(TreeNode* root) {
		return getdepth(root);
	}
};
class isBinaryTreeBalanced {
public:
	int getdepth(TreeNode* node) {
		if (node == nullptr) {
			return 0;
		}
		int leftDepth = getdepth(node->left);
		if (leftDepth == -1)return -1;
		int rightDepth = getdepth(node->right);
		if (rightDepth == -1)return -1;
		return abs(leftDepth - rightDepth) > 1 ? -1 : 1 + max(leftDepth, rightDepth);
	}
	bool isbalanced(TreeNode* root) {
		return getdepth(root) == -1 ? false : true;
	}
};

//strings, ints and overflows
int gcd(int x, int y) {
	int z = y;
	while (x % y != 0) {
		z = x % y;
		x = y;
		y = z;
	}
	return z;
}
int intOverFlow(unsigned int i, unsigned int j) {//判断两个无符号整形相加产生溢出
	int sum = 0;
	sum = (int)(i + j - pow(2, 32));
	if (sum < i && sum < j) {

		return 1;

	}

	return 0;
}
class AddtwoNumber {
public:
	int add(int a, int b) {

		int n, m;
		while (b != 0) {
			//这是无进位的情况。
			n = a ^ b;
			//进位的。
			m = (unsigned int)(a & b) << 1; // 转换成无符号数。可能有负数的情况。
			a = n;
			b = m;  // 一直到进位的情况为 0，退出循环。
		}
		return a;
	}
};

class split {
public:
	int strToInt(string str) {
		int i = 0, flag = 1;
		long res = 0;
		while (str[i] == ' ') i++;
		if (str[i] == '-') flag = -1;
		if (str[i] == '-' || str[i] == '+') i++;
		for (; i < str.size() && isdigit(str[i]); i++) {
			res = res * 10 + (str[i] - '0');
			if (res >= INT_MAX && flag == 1) return INT_MAX;
			if (res > INT_MAX && flag == -1)return INT_MIN;
		}
		return flag * res;
	}
	vector<int> Split(string str, char pattern) {
		vector<int> res;
		string temp;
		string num;
		for (auto i : str) {
			if (isdigit(i)||i==pattern||i=='+'||i=='-') {//clean string to make sure no special char
				temp.push_back(i);
			}
		}
		temp += pattern;
		cout << temp;
		for (auto i : temp) {
			if (i != pattern) {
				num.push_back(i);
			}
			else if(i==pattern&&num!=""){
					res.push_back(strToInt(num));
					num.clear();
			}
			//else if (i == pattern && num == "") {
			//	continue;
			//}
			
		}
		return res;
	}
};
class offer67 {//str to int
public:
	int strToInt(string str) {
		int i = 0, flag = 1;
		long res = 0;
		while (str[i] == ' ') i++;
		if (str[i] == '-') flag = -1;
		if (str[i] == '-' || str[i] == '+') i++;
		for (; i < str.size() && isdigit(str[i]); i++) {
			res = res * 10 + (str[i] - '0');
			if (res >= INT_MAX && flag == 1) return INT_MAX;
			if (res > INT_MAX && flag == -1)return INT_MIN;
		}
		return flag * res;
	}
};
//array
class MergeSortedArray {
public:






};
class offer03 {//剑指 Offer 03. 数组中重复的数字
public:
	int findRepeatNumber(vector<int>& nums) {
		for (int i = 0; i < nums.size(); i++) {
			while (nums[i] != i) {
				if (nums[i] == nums[nums[i]]) {
					return nums[i];
				}
				swap(nums[i], nums[nums[i]]);
			}
		}
		return -1;
	}
};
class Leetcode384 {//shuffle the cards
private:
	vector<int> data;
public:
	Leetcode384(vector<int>& nums) {
		data = nums;
	}
	vector<int> reset() {
		return data;
	}
	vector<int> shuffle() {
		vector<int> res(data);
		for (int i = 0; i < res.size(); i++) {
			swap(res[i], res[rand() % (i + 1)]);
		}
		return res;
	}
};
class fib {
public:
	int climbStairs(int n) {//dp, saves time complexity
		vector<int> dp(n + 3);
		dp[1] = 1;
		dp[2] = 2;
		for (int i = 3; i <= n; i++)
			dp[i] = dp[i - 1] + dp[i - 2];
		return dp[n];
	}


};
class Leetcode35 {//binary search
public:
	int searchInsert(vector<int>& nums, int target) {
		int n = nums.size();
		int left = 0;
		int right = n - 1;
		while (left <= right) {
			int middle = left + ((right - left) / 2);
			if (nums[middle] > target) {// target 在左区间，所以[left, middle - 1]
				right = middle - 1;
			}
			else if (nums[middle] < target) {
				left = middle + 1;// target 在右区间，所以[middle + 1, right]
			}
			else {
				return middle;
			}
		}
		// 分别处理如下四种情况
		// 目标值在数组所有元素之前  [0, -1]
		// 目标值等于数组中某一个元素  return middle;
		// 目标值插入数组中的位置 [left, right]，return  right + 1
		// 目标值在数组所有元素之后的情况 [left, right]， return right + 1
		return right + 1;
	}
};
class Leetcode26 {
public:
	int removeDuplicates(vector<int> nums) {//remove duplicate element
		int length = nums.size();
		if (length == 0) {
			return 0;
		}
		int slow = 0, fast = 0;
		while (fast < length) {
			if (nums[fast] != nums[slow]) {
				slow++;
				// 维护 nums[0..slow] 无重复
				nums[slow] = nums[fast];
			}
			fast++;
		}
		// 数组长度为索引 + 1
		return slow + 1;
	}

};
class Leetcode27 {//remove element, given value
public:
	int removeElement(vector<int>& nums, int val) {//bruteforce
		int size = nums.size();
		for (int i = 0; i < size; i++) {
			if (nums[i] == val) { // 发现需要移除的元素，就将数组集体向前移动一位
				for (int j = i + 1; j < size; j++) {
					nums[j - 1] = nums[j];
				}
				//cout << nums[i] << endl;
				i--;// 因为下表i以后的数值都向前移动了一位，所以i也向前移动一位
				//cout << nums[i] << endl;
				size--;// 此时数组的大小-1

			}
		}
		return size;
	}
	int removeElementDoubleP(vector<int>& nums, int val) {
		//双指针法
		int slowIndex = 0;
		for (int fastIndex = 0; fastIndex < nums.size(); fastIndex++) {
			if (val != nums[fastIndex]) {
				nums[slowIndex++] = nums[fastIndex];
			}
		}
		return slowIndex;
	}
};
class Leetcode209 {
public:
	int minSubArrayLen(int s, vector<int>& nums) {
		int result = INT32_MAX;
		int sum = 0;
		int subLength = 0;
		for (int i = 0; i < nums.size(); i++) {
			sum = 0;
			for (int j = i; j < nums.size(); j++) {
				if (sum >= s) {
					subLength = j - i + 1;
					result = result < subLength ? result : subLength;
					break;
				}
			}

		}
		return result == INT32_MAX ? 0 : result;
	}

	int minSubArrayLenSlidingWindow(int s, vector<int>& nums) {
		int result = INT32_MAX;
		int sum = 0;
		int subLength = 0;
		int i = 0;
		for (int j = 0; j < nums.size(); j++) {
			sum += nums[j];
			while (sum >= s) {
				subLength = (j - i + 1);
				result = result < subLength ? result : subLength;
				sum -= nums[i++];
			}
		}
		return result == INT32_MAX ? 0 : result;
	}
};

class Leetcode59 {//SpiralMatrix
public:
	vector<vector<int>> SpiralMatrix(int n) {
		vector<vector<int>> res(n, vector<int>(n, 0));
		int startx = 0, starty = 0; // 定义每循环一个圈的起始位置
		int loop = n / 2; // 每个圈循环几次，例如n为奇数3，那么loop = 1 只是循环一圈，矩阵中间的值需要单独处理
		int mid = n / 2; // 矩阵中间的位置，例如：n为3， 中间的位置就是(1，1)，n为5，中间位置为(2, 2)
		int count = 1; // 用来给矩阵中每一个空格赋值
		int offset = 1; // 每一圈循环，需要控制每一条边遍历的长度
		int i, j;
		while (loop--) {
			i = startx;
			j = starty;

			// 下面开始的四个for就是模拟转了一圈
			// 模拟填充上行从左到右(左闭右开)
			for (j = starty; j < starty + n - offset; j++) {
				res[startx][j] = count++;
			}
			// 模拟填充右列从上到下(左闭右开)
			for (i = startx; i < startx + n - offset; i++) {
				res[i][j] = count++;
			}
			// 模拟填充下行从右到左(左闭右开)
			for (; j > starty; j--) {
				res[i][j] = count++;
			}
			// 模拟填充左列从下到上(左闭右开)
			for (; i > startx; i--) {
				res[i][j] = count++;
			}

			// 第二圈开始的时候，起始位置要各自加1， 例如：第一圈起始位置是(0, 0)，第二圈起始位置是(1, 1)
			startx++;
			starty++;

			// offset 控制每一圈里每一条边遍历的长度
			offset += 2;
		}

		// 如果n为奇数的话，需要单独给矩阵最中间的位置赋值
		if (n % 2) {
			res[mid][mid] = count;
		}
		return res;
	}
};
class Leetcode344 {//reverseString
public:
	void reverseString(vector<char>& s) {
		for (int i = 0, j = s.size() - 1; i < s.size() / 2; i++, j--) {
			swap(s[i], s[j]);
		}
	}
};
//linkedlist
class Leetcode203 {
public:
	ListNode* removeElements(ListNode* head, int val) {
		ListNode* dummyHead = new ListNode(0); // 设置一个虚拟头结点
		dummyHead->next = head; // 将虚拟头结点指向head，这样方面后面做删除操作
		ListNode* cur = dummyHead;

		while (cur->next != nullptr) {
			if (cur->next->val == val) {
				//cout << cur->next->val;
				ListNode* tmp = cur->next;
				cur->next = cur->next->next;
				delete tmp;
			}
			else {
				cur = cur->next;
			}
		}
		return dummyHead->next;
	}
};

ostream& operator<<(ostream& str, const SinglyLinkedList& L) {
	str << "<< ";
	ListNode* p = L.head;
	while (p) {
		str << p->val << " ";
		p = p->next;//a common error p++;
	}
	str << ">>";

	return str;
}
class sortLinkedList {
public:
	ListNode* selectSortList(ListNode* head) {
		//selection sort
		if (head == nullptr || head->next == nullptr) return head;
		ListNode* pstart = new ListNode(0);
		pstart->next = head;
		ListNode* sortedTail = pstart;
		while (sortedTail->next != nullptr) {
			ListNode* minNode = sortedTail->next, * p = sortedTail->next->next;
			while (p != nullptr) {
				if (p->val < minNode->val) {
					minNode = p;
				}
				p = p->next;
			}
			swap(minNode->val, sortedTail->next->val);
			sortedTail = sortedTail->next;
		}
		head = pstart->next;
		delete pstart;
		return head;
	}
	ListNode* partitionList(ListNode* low, ListNode* high) {
		int key = low->val;
		ListNode* loc = low;
		for (ListNode* i = low->next; i != high; i = i->next) {
			if (i->val < key) {
				loc = loc->next;
				swap(i->val, loc->val);
			}
		}
		swap(loc->val, low->val);
		return loc;
	}
	void qsortList(ListNode* head, ListNode* tail) {
		if (head != tail && head->next != tail) {
			ListNode* mid = partitionList(head, tail);
			qsortList(head, mid);
			qsortList(mid->next, tail);
		}
	}
	ListNode* quickSortList(ListNode* head) {
		if (head == nullptr || head->next == nullptr) return head;
		qsortList(head, nullptr);
		return head;
	}

};
class Leetcode206 {//reverse linkedlist
public:
	ListNode* reverseLinkedList(ListNode* head) {
		ListNode* cur = head;
		ListNode* pre = nullptr;
		ListNode* tmp;
		while (cur) {
			tmp = cur->next;
			cur->next = pre;
			pre = cur;
			cur = tmp;
		}
		return pre;
	}
};
void printLL(ListNode* head) {//print linkedlist
	cout << "<";
	while (head) {
		cout << head->val;
		cout << " ";
		head = head->next;
	}
	cout << ">"<<endl;
}
class Leetcode142 {
public:
	ListNode* detectCycle(ListNode* head) {
		ListNode* fast = head;
		ListNode* slow = head;
		while (fast != NULL && fast->next != NULL) {
			slow = slow->next;
			fast = fast->next->next;
			// 快慢指针相遇，此时从head 和 相遇点，同时查找直至相遇
			if (slow == fast) {
				ListNode* index1 = fast;
				ListNode* index2 = head;
				while (index1 != index2) {
					index1 = index1->next;
					index2 = index2->next;
				}
				return index2; // 返回环的入口
			}
		}
		return NULL;
	}
};
class GetIntersection {
public:
	ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
		if (headA == nullptr || headB == nullptr) {
			return nullptr;
		}
		ListNode* pa = headA;
		ListNode* pb = headB;
		int flag = 0;
		while (pa != pb) {
			if (pa != nullptr) pa = pa->next;
			else pa = headB;
			if (pb != nullptr) pb = pb->next;
			else pb = headA;
		}
		return pa;
	}
};
class Leetcode83 {//给定一个排序链表，删除所有重复的元素，使得每个元素只出现一次。
public:
	ListNode* deleteDuplicates(ListNode* head) {
		ListNode* pi = head;
		while (pi && pi->next) {
			if (pi->val == pi->next->val) {
				ListNode* del = pi->next;
				pi->next = pi->next->next;
				delete del;
			}
			else {
				pi = pi->next;
			}
		}
		return head;
	}
};
//Stack and queue
class MinStack_optimal {
	stack<int> x_stack;
	stack<int> max_stack;
	int min;
	int max;
public:
	void push(int x) {
		if (x_stack.empty()) {
			min = x;
			max = x;
			x_stack.push(0);
			max_stack.push(0);
		}
		else {
			int compare = x - min;
			int compare_max = x - max;
			x_stack.push(compare);
			max_stack.push(compare_max);
			min = compare < 0 ? x : min;
			max = compare_max > 0 ? x : max;
		}
	}
	void pop() {
		int top = x_stack.top();
		int max_top = max_stack.top();
		min = top < 0 ? (min - top) : min;
		cout << "pop! Max is:"<<max<<" max top is: "<<max_top << endl;
		max = max_top > 0 ? (max - max_top) : max;

		x_stack.pop();
		max_stack.pop();
	}
	int getMin() {
		return min;
	}
	int getMax() {
		return max;
	}
	int top() {
		//int save_min = this->min;
		int save_top = x_stack.top();
		this->pop();
		int res = save_top + min;
		this->push(res);
		return res;
	}
};
class MinMaxStack {//Leetcode155
	stack<int> x_stack;
	stack<int> min_stack;
	stack<int> max_stack;
public:
	MinMaxStack() {
		min_stack.push(INT_MAX);
		max_stack.push(INT_MIN);
	}
	void push(int x) {
		x_stack.push(x);
		min_stack.push(min(x, min_stack.top()));
		max_stack.push(max(x, max_stack.top()));
	}
	void pop() {
		x_stack.pop();
		min_stack.pop();
		max_stack.pop();
	}
	int top() {
		return x_stack.top();
	}
	int getMin() {
		return min_stack.top();
	}
	int getMax() {
		return max_stack.top();
	}
};
class Mystack {//Leetcode225, 用队列实现栈
public:
	queue<int> q;
	Mystack() {

	}

	/** Push element x onto stack. */
	void push(int x) {
		int n = q.size();
		q.push(x);
		for (int i = 0; i < n; i++) {
			q.push(q.front());
			q.pop();
		}

	}

	/** Removes the element on top of the stack and returns that element. */
	int pop() {
		int r = q.front();
		q.pop();
		return r;
	}

	/** Get the top element. */
	int top() {
		int r = q.front();
		return r;
	}

	/** Returns whether the stack is empty. */
	bool empty() {
		return q.empty();

	}
};
class MyQueue {
public:
	stack<int> stIn;
	stack<int> stout;
	/** Initialize your data structure here. */
	MyQueue() {

	}
	/** Push element x to the back of queue. */
	void push(int x) {
		stIn.push(x);
	}
	/** Removes the element from in front of queue and returns that element. */
	int pop() {
		// 只有当stOut为空的时候，再从stIn里导入数据（导入stIn全部数据）
		if (stout.empty()) {
			// 从stIn导入数据直到stIn为空
			while (!stIn.empty()) {
				stout.push(stIn.top());//// 因为pop函数弹出了元素res，所以再添加回去
				stIn.pop();
			}
		}
		int res = stout.top();
		stout.pop();
		return res;
	}
	/** Get the front element. */
	int peek() {
		int res = this->pop();
		stout.push(res);
		return res;
	}
	/** Returns whether the queue is empty. */
	bool empty() {
		return stIn.empty() && stout.empty();
	}
};
class MyCircularQueue {
private:
	vector<int> vec;
	int head, tail;
	int max_size;
	int cur_size;
public:
	/** Initialize your data structure here. Set the size of the queue to be k. */
	MyCircularQueue(int k):max_size(k),head(0),tail(0),vec(vector<int>(k)),cur_size(0) {

	}

	/** Insert an element into the circular queue. Return true if the operation is successful. */
	bool enQueue(int value) {
		if (this->isFull()) {
			return false;
		}
		if (this->cur_size != 0) {
			// 考虑如果 这时是空队列， 那么需要再原地添加（tail不移动）， 而不需要后移位置
			this->tail = (++this->tail) % this->max_size;
		}
		this->vec[this->tail] = value;
		this->cur_size++;
		return true;
	}

	/** Delete an element from the circular queue. Return true if the operation is successful. */
	bool deQueue() {
		if (this->isEmpty()) {
			return false;
		}
		this->cur_size--;
		if (this->cur_size != 0) // 如果dequeue之后为空，那么head将不移动， 否则后移一位
			this->head = (++this->head) % this->max_size;

		return true;
	}

	/** Get the front item from the queue. */
	int Front() {
		if (this->isEmpty())
			return -1;
		return this->vec[this->head];
	}

	/** Get the last item from the queue. */
	int Rear() {
		if (this->isEmpty())
			return -1;
		return this->vec[this->tail];
	}

	/** Checks whether the circular queue is empty or not. */
	bool isEmpty() {
		if (this->cur_size == 0) {
			return true;
		}
		return false;
	}

	/** Checks whether the circular queue is full or not. */
	bool isFull() {
		if (this->cur_size == this->max_size) {
			return true;
		}
		return false;
	}
};

/**
 * Your MyCircularQueue object will be instantiated and called as such:
 * MyCircularQueue* obj = new MyCircularQueue(k);
 * bool param_1 = obj->enQueue(value);
 * bool param_2 = obj->deQueue();
 * int param_3 = obj->Front();
 * int param_4 = obj->Rear();
 * bool param_5 = obj->isEmpty();
 * bool param_6 = obj->isFull();
 */
class Leetcode20 {
public:
	bool isValid(string s) {
		stack<int> st;
		for (int i = 0; i < s.size(); i++) {
			if (s[i] == '(') st.push(')');
			else if (s[i] == '{') st.push('}');
			else if (s[i] == '[') st.push(']');
			// 第三种情况：遍历字符串匹配的过程中，栈已经为空了，没有匹配的字符了，说明右括号没有找到对应的左括号 return false
			// 第二种情况：遍历字符串匹配的过程中，发现栈里没有我们要匹配的字符。所以return false
			else if (st.empty() || st.top() != s[i]) return false;
			else st.pop(); // st.top() 与 s[i]相等，栈弹出元素
		}
		// 第一种情况：此时我们已经遍历完了字符串，但是栈不为空，说明有相应的左括号没有右括号来匹配，所以return false，否则就return true
		return st.empty();
	}
};
//hashset
class three_sum {//threesum
public:
	vector<vector<int>> threesum(vector<int>& nums) {
		vector<vector<int>> result;
		sort(nums.begin(), nums.end());
		for (int i = 0; i < nums.size(); i++) {
			if (nums[i] > 0) {
				return result;
			}
			if (i > 0 && nums[i] == nums[i - 1]) {
				continue;
			}
			int left = i + 1;
			int right = nums.size() - 1;
			while (right>left) {
			

			
			if (nums[i] + nums[left] + nums[right] > 0) {
				right--;
			}
			else if (nums[i] + nums[left] + nums[right] < 0) {
				left++;
			}
			else {
				result.push_back(vector<int>{nums[i], nums[left], nums[right]});
				while (right > left && nums[right] == nums[right - 1]) {
					right--;
				}
				while (right > left && nums[left] == nums[left + 1]) {
					left++;
				}
				right--;
				left++;
			}
		  }
		}
		return result;
	}
};
class two_sum {//twosum
public:
	vector<int> twosum(vector<int>& nums, int target) {
		unordered_map<int, int> hashtable;
		for (int i = 0; i < nums.size(); i++) {
			auto it = hashtable.find(target - nums[i]);
			if (it != hashtable.end()) {
				return{ it->second,i };
			}
			hashtable[nums[i]] = i;
		}
		return {};
	}
};
class Leetcode611 {//number of tuple that can form a triangle in an array
public:
	int triangleNumber(vector<int>& nums) {
		if (nums.size() < 3) return 0;
		sort(nums.begin(),nums.end(),greater<int>());
		int res = 0;
		int N = nums.size();
		for (int i = 0; i < N - 2; ++i) {
			int l = i + 1;
			int r = N - 1;
			while (l < r) {
				if (nums[l] + nums[r] <= nums[i]) {
					--r;
				}
				else {
					res += r - l;
					++l;
				}
			}

		}
		return res;
	}
};

class topk {//sort
public:
	static bool cmp(pair<int, int>& m, pair<int, int>& n) {
		return m.second > n.second;
	}

	vector<int> topk_Frequent(vector<int>& nums, int k) {
		unordered_map<int, int> occurrences;
		for (auto& v : nums) {
			occurrences[v]++;
		}

		// pair 的第一个元素代表数组的值，第二个元素代表了该值出现的次数
		priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(&cmp)> q(cmp);
		for (auto& i : occurrences) {
			if (q.size() == k) {
				if (q.top().second < i.second) {
					q.pop();
					q.emplace(i.first, i.second);
				}
			}
			else {
				q.emplace(i.first, i.second);
			}
		}
		vector<int> ret;
		while (!q.empty()) {
			ret.emplace_back(q.top().first);
			q.pop();
		}
		return ret;
	}
	vector<int> getLeastNumbers(vector<int>& arr, int k) {
		vector<int> vec(k, 0);
		sort(arr.begin(), arr.end());
		for (int i = 0; i < k; ++i) {
			vec[i] = arr[i];
		}
		return vec;
	}
	vector<int> getLeastNumbers_heap(vector<int>& arr, int k) {
		vector<int> vec(k, 0);
		if (k == 0) {//exclude the conditon where k is zero
			return vec;
		}
		priority_queue<int> Q;
		for (int i = 0; i < k; ++i) {
			Q.push(arr[i]);
		}
		for (int i = k; i < (int)arr.size(); ++i) {
			if (Q.top() > arr[i]) {
				Q.pop();
				Q.push(arr[i]);
			}
		}
		for (int i = 0; i < k; ++i) {
			vec[i] = Q.top();
			Q.pop();
		}
		return vec;
	}

};
class SortAlgorithm {
public:
	int parititon(vector<int>& vi, int low, int up) {
		int pivot = vi[up];
		int i = low - 1;
		for (int j = low; j < up; j++)
		{
			if (vi[j] <= pivot)
			{
				i++;
				swap(vi[i], vi[j]);
			}
		}
		swap(vi[i + 1], vi[up]);
		return i + 1;

	}

	void quickSort(vector<int>& vi, int low, int up)
	{
		if (low < up)
		{
			int mid = SortAlgorithm::parititon(vi, low, up);
			//Watch out! The mid position is on the place, so we don't need to consider it again.
			//That's why below is mid-1, not mid! Otherwise it will occur overflow error!!!
			quickSort(vi, low, mid - 1);
			quickSort(vi, mid + 1, up);
		}
	}
	void qSort(vector<int>& vi)
	{
		quickSort(vi, 0, vi.size() - 1);
	}
};
ostream& operator<<(ostream & str, const vector<int> & arr) {
	str << "<";
	for (auto const& i : arr) {
		str << " " << i;
	}
	str << " >";
	return str;
}
ostream& operator<<(ostream& str, const vector<string>& arr) {
	str << "<";
	for (auto const& i : arr) {
		str << " " << i;
	}
	str << " >";
	return str;
}
//some Greedy Problems
class Distribute_candy {//Leetcode 135
public:
	int candy(vector<int>& ratings) {
		int size = ratings.size();
		if (size < 2) {
			return size;
		}
		vector<int> num(size, 1);
		for (int i = 1; i < size; i++) {//left to right
			if (ratings[i] > ratings[i - 1]) {
				num[i] = num[i - 1] + 1;
			}
		}
		for (int j = size - 1; j > 0; j--) {
			if (ratings[j] < ratings[j - 1]) {
				num[j - 1] = max(num[j - 1], num[j] + 1);
			}
		}
		int sum = 0;
		for (auto const& i : num) {
			sum += i;
		}
		return sum;
	}
};
class maximum_subArray {//最大子序和
public:
	int maxSubArray_bruteForce(vector<int>& nums) {
		int result = INT32_MIN;
		int count = 0;
		for (int i = 0; i < nums.size(); i++) {
			count = 0;
			for (int j = i; j < nums.size(); j++) {
				count += nums[j];
				result = count > result ? count : result;
			}
		}
		return result;
	}
	int maxSubArray_Greedy(vector<int>& nums){
		int result = INT32_MIN;
		int count = 0;
		for (int i = 0; i < nums.size(); i++) {
			count += nums[i];
			if (count > result) {
				result = count;
			}
			if (count <= 0) count = 0;
		}
		return result;
	}
};
class BuyStock {
public:
	int maxProfit_single(vector<int>& prices) {//单次交易
		int inf = 1e9;
		int minprice = inf, maxprofit = 0;
		for (int price : prices) {
			maxprofit = max(maxprofit, price - minprice);
			minprice = min(price, minprice);
		}
		return maxprofit;
	}
	int maxProfit(vector<int>& prices) {//多次交易版
		int result = 0;
		for (int i = 1; i < prices.size(); i++) {
			result += max(prices[i] - prices[i - 1], 0);
		}
		return result;
	}
};
shared_ptr<int>Copy(shared_ptr<int> sp) {
	shared_ptr<int> a = move(sp);
	return shared_ptr<int>(a);
}
class Singleton {
private:
	Singleton();//set to private, or compiler will generate as public
	Singleton(const Singleton& other);
public:
	static Singleton* getInstance();
	static Singleton* m_instance;
};

Singleton* Singleton::m_instance = nullptr;//initialize static variable to null
//// thread not safe: if two threads go to if at the same time, m_instance would be created twice
//Singleton* Singleton::getInstance() {
//	if (m_instance == nullptr) {
//		m_instance = new Singleton();
//	}
//	return m_instance;
//}
////thread safe, but high cost brought by lock
//Singleton* Singleton::getInstance() {
//	mutex mtx;//?, read op does not need lock
//	mtx.lock();//huge cost when high concurrency
//	if (m_instance == nullptr) {
//		m_instance = new Singleton();
//	}
//	return m_instance;
//}

////内存读写reorder导致不安全，构造器的指令执行顺序可能不同
//Singleton* Singleton::getInstance() {
//	if (m_instance == nullptr) {//避免不是都不是null的时候进行读操作代价过高
//		mutex mtx;//?, read op does not need lock
//		mtx.lock();//huge cost when high concurrency
//		if (m_instance == nullptr) {//避免为null时两个线程同事进入到第一个if之后
//			m_instance = new Singleton();//分配内存，调用构造器，赋值地址？
//			//分配内存，赋值地址，调用构造器导致reorder
//		}
//	}
//	return m_instance;
//}
class LCS {//最长子序列
public:
	int longestCommonSubsequence(string text1, string text2) {
		const int rows = text1.size();
		const int cols = text2.size();
		vector<vector<int>> dp(rows, vector<int>(cols, 0));
		// 求解边界 BEGIN
		if (text1[0] == text2[0])
			dp[0][0] = 1;
		for (int i = 1; i < rows; i++) {
			dp[i][0] = dp[i - 1][0];
			if (text1[i] == text2[0]) {
				dp[i][0] = 1;
			}
		}
		for (int j = 1; j < cols; j++) {
			dp[0][j] = dp[0][j - 1];
			if (text1[0] == text2[j]) {
				dp[0][j] = 1;
			}
		}
		// 求解边界 END

		for (int i = 1; i < rows; i++)
			for (int j = 1; j < cols; j++) {
				if (text1[i] == text2[j]) { // 遇到匹配字符
					dp[i][j] = dp[i - 1][j - 1] + 1;
				}
				else { // 不匹配时，继承左上中的较大值
					dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
				}
			}
		return dp[rows - 1][cols - 1];
	}
	int LongestCommonSubstring(string s1, string s2) {
		if (s1 == "" || s2 == "") {
			return 0;
		}
		int m = s1.size();
		int n = s2.size();
		vector<vector<int>> table(m + 1, vector<int>(n + 1));

		int biggest = 0;// 记录表中最大值
		for (int i = 0; i < m + 1; ++i) {
			for (int j = 0; j < n + 1; ++j) {
				if (i == 0 || j == 0) {
					table[i][j] = 0;
				}

				else if (s1[i - 1] == s2[j - 1]) {
					table[i][j] = table[i - 1][j - 1] + 1;
					if (table[i][j] > biggest) {
						biggest = table[i][j];
					}
				}
				else {
					table[i][j] = 0;
				}
			}
		}
		return biggest;
	}

	void printLCString(string s1, string s2)
	{
		if (s1 == "" || s2 == "")
			return;

		int m = s1.size();
		int n = s2.size();
		vector<vector<int> > table(m + 1, vector<int>(n + 1));

		int biggest = 0;  // 记录表中最大值
		vector<pair<int, int> > firstPos;  // 记录子串开始的坐标 
		for (int i = 0; i < m + 1; ++i)
		{
			for (int j = 0; j < n + 1; ++j)
			{
				// 第一行和第一列置0  
				if (i == 0 || j == 0)
					table[i][j] = 0;
				else if (s1[i - 1] == s2[j - 1])
				{
					table[i][j] = table[i - 1][j - 1] + 1;
					if (table[i][j] > biggest)
						biggest = table[i][j];
					if (table[i][j] == 1)
						firstPos.push_back(make_pair(i, j));
				}
				else  // 不相等置0
					table[i][j] = 0;
			}
		}

		// 输出所有的最长公共子串
		vector<pair<int, int> >::iterator beg = firstPos.begin();
		for (; beg != firstPos.end(); ++beg)
		{
			int start1 = beg->first - 1;
			int start2 = beg->second - 1;
			if (s1.substr(start1, biggest) == s2.substr(start2, biggest))
				cout << s1.substr(start1, biggest) << endl;
		}
	}
};
class trappingRainWater {
public:
	int trap(vector<int>& height) {
		if (height.empty()) {
			return 0;
		}
		int ans = 0;
		int size = height.size();
		vector<int> left_max(size);
		vector<int> right_max(size);
		left_max[0] = height[0];
		for (int i = 1; i < size; i++) {
			left_max[i] = max(height[i], left_max[i - 1]);
		}
		right_max[size - 1] = height[size - 1];
		for (int i = size - 2; i >= 0; i--) {
			right_max[i] = max(height[i], right_max[i + 1]);
		}
		for (int i = 1; i < size - 1; i++) {
			ans += min(left_max[i], right_max[i]) - height[i];
		}
		return ans;

	}
};
class LongestSubstringLength {//3. 无重复字符的最长子串
public:
	int LengthofLongestSubstring(string s) {
		// 哈希集合，记录每个字符是否出现过
		unordered_set<char> occ;
		int n = s.size();
		// 右指针，初始值为 -1，相当于我们在字符串的左边界的左侧，还没有开始移动
		int rk = -1, ans = 0;
		// 枚举左指针的位置，初始值隐性地表示为 -1
		for (int i = 0; i < n; ++i) {
			if (i != 0) {
				// 左指针向右移动一格，移除一个字符
				occ.erase(s[i - 1]);
			}
			while (rk + 1 < n && !occ.count(s[rk + 1])) {
				// 不断地移动右指针
				occ.insert(s[rk + 1]);
				++rk;
			}
			// 第 i 到 rk 个字符是一个极长的无重复字符子串
			ans = max(ans, rk - i + 1);
		}
		return ans;
	}
};
class MoreThanHalf {//数组中出现次数超过一半的数字
public:
	int major_element(vector<int>& nums) {
		unordered_map<int, int> match;
		int len = nums.size();
		int res = 0;
		if (len == 1 || len == 2) {
			return nums[0];
		}
		for (int i = 0; i < len; i++) {
			match[nums[i]]++;
			if (match[nums[i]] > (len / 2)) {
				res = nums[i];
				break;
			}
		}
		return res;
	}
	int major_element_vote(vector<int>& nums) {
		int x = 0;
		int votes = 0;
		for (int num : nums) {
			if (votes == 0) x = num;
			votes += num == x ? 1 : -1;
		}
		return x;

	}
};
class medianFinder {
	priority_queue<int> lo; //max heap
	priority_queue<int, vector<int>, greater<int>> hi; //min heap
public:
	void addNum(int num) {
		lo.push(num);// Add to max heap

		hi.push(lo.top());// balancing step
		lo.pop();

		if (lo.size() < hi.size()) {                     // maintain size property
			lo.push(hi.top());
			hi.pop();
		}

	}
	double findMedian() {
		return lo.size() > hi.size() ? (double)lo.top() : (lo.top() + hi.top()) * 0.5;
	}
	
};
class QuickSortLL {
public:
	ListNode* quickSortList(ListNode* head) {
		// IMPORTANT: Please reset any member data you declared, as
		// the same Solution instance will be reused for each test case.
		//链表快速排序
		if (head == NULL || head->next == NULL)return head;
		ListNode tmpHead(0); tmpHead.next = head;
		qsortList(&tmpHead, head, NULL);
		return tmpHead.next;
	}
	void qsortList(ListNode* headPre, ListNode* head, ListNode* tail)
	{
		//链表范围是[low, high)
		if (head != tail && head->next != tail)
		{
			ListNode* mid = partitionList(headPre, head, tail);//注意这里head可能不再指向链表头了
			qsortList(headPre, headPre->next, mid);
			qsortList(mid, mid->next, tail);
		}
	}
	ListNode* partitionList(ListNode* lowPre, ListNode* low, ListNode* high)
	{
		//链表范围是[low, high)
		int key = low->val;
		ListNode node1(0), node2(0);//比key小的链的头结点，比key大的链的头结点
		ListNode* little = &node1, * big = &node2;
		for (ListNode* i = low->next; i != high; i = i->next)
			if (i->val < key)
			{
				little->next = i;
				little = i;
			}
			else
			{
				big->next = i;
				big = i;
			}
		big->next = high;//保证子链表[low,high)和后面的部分连接
		little->next = low;
		low->next = node2.next;
		lowPre->next = node1.next;//为了保证子链表[low,high)和前面的部分连接
		return low;
	}
};
class ReverseKGroup {
public:
	pair<ListNode*, ListNode*> myReverse(ListNode* head, ListNode* tail) {
		ListNode* prev = tail->next;
		ListNode* p = head;
		while (prev != tail) {
			ListNode* nex = p->next;
			p->next = prev;
			prev = p;
			p = nex;
		}
		return { tail,head };
	}
	ListNode* reverseKGroup(ListNode* head, int k) {
		ListNode* hair = new ListNode(0);
		hair->next = head;
		ListNode* pre = hair;

		while (head)
		{
			ListNode* tail = pre;
			for (int i = 0; i < k; ++i) {
				tail = tail->next;
				if (!tail) {
					return hair->next;
				}
			}
			ListNode* nex = tail->next;
			pair<ListNode*, ListNode*> result = myReverse(head, tail);
			head = result.first;
			tail = result.second;
			pre->next = head;
			tail->next = nex;
			pre = tail;
			head = tail->next;
		}
		return hair->next;
	}
};
class LongestIncreasingSubsequence {
public:
	int lengthofLIS(vector<int>& nums) {
		int n = (int)nums.size();
		if (n == 0) return 0;
		vector<int> dp(n, 0);
		for (int i = 0; i < n; ++i) {
			dp[i] = 1;
			for (int j = 0; j < i; ++j) {
				if (nums[j] < nums[i]) {
					dp[i] = max(dp[i], dp[j] + 1);
				}
			}
		}
		return *max_element(dp.begin(), dp.end());
	}

};
class reversewords {
public:
	string reverseWords(string s) {
		string str;
		if (s.empty())  //输入字符为空，返回空
			return str;
		cout << s.size() << endl;
		int i{ 0 }, j{ 0 };  //i，j用来表示单词开始和结束的位置
		j = s.size() - 1;
		for (j; j >= 0; --j)
		{
			if (s[j] != ' ')  //遇到不是空格的
			{
				i = j;
				while (i >= 0 && s[i] != ' ')  //从j开始向左寻找单词，i>=0防止越界访问
					--i;
				for (int k = i + 1; k <= j; ++k)  //单词序列加入字符串中
					str.push_back(s[k]);
				str.push_back(' ');  //加入一个空格
				j = i;  //改变j的位置
			}
		}
		if (str.size() > 0)
			str.pop_back();  //移除末尾空格
		return str;
	}
};

int main() {
	Leetcode35 SearchInsertPosition;
	vector<int> arr{1, 3, 5, 6};
	cout << "SearchInsertPosition: "<<SearchInsertPosition.searchInsert(arr, 7) << endl;
	Leetcode27 RemoveElement;
	//cout << "RemoveElement: "<<RemoveElement.removeElement(arr, 3)<<endl;

	cout << "RemoveElement: " << RemoveElement.removeElementDoubleP(arr, 5) << endl;
	Leetcode209 SlidingWindow209;
	vector<int> nums{ 2,3,1,2,4,3 };
	cout << "minSubArrayLenSlidingWindow: " << SlidingWindow209.minSubArrayLenSlidingWindow(7, nums) << endl;
	
	ListNode *head = new ListNode(1);
	ListNode *a = new ListNode(2);
	ListNode* b = new ListNode(6);
	ListNode* c = new ListNode(3);
	ListNode* d = new ListNode(4);
	ListNode* e = new ListNode(5);
	ListNode* f = new ListNode(6);
	head->next = a;
	a->next = b;
	b->next = c;
	c->next = d;
	d->next = e;
	e->next = f;
	cout << endl;
	Leetcode203 RemoveLLElement;
	ListNode* newHead = RemoveLLElement.removeElements(head, 6);
	printLL(newHead);
	cout << endl;
	SinglyLinkedList LL{ 1,2,3,4 };
	cout << LL << endl;
	ListNode* HHead = RemoveLLElement.removeElements(LL.head, 3);
	cout << LL << endl;
	Leetcode206 ReverseLL;
	ListNode* ReverseHead = ReverseLL.reverseLinkedList(LL.head);
	//while (ReverseHead) {
	//	cout << ReverseHead->val;
	//	ReverseHead = ReverseHead->next;
	//}
	printLL(ReverseHead);
	ListNode* cyclehead = new ListNode(3);
	ListNode* cycleheadA = new ListNode(0);
	ListNode* cycleheadB = new ListNode(2);
	ListNode* cycleheadC = new ListNode(-4);
	cyclehead->next = cycleheadA;
	cycleheadA->next = cycleheadB;
	cycleheadB->next = cycleheadC;
	cycleheadC->next = cycleheadA;
	Leetcode142 DetectCycle;
	cout<<"Cycle Entry Point: "<< DetectCycle.detectCycle(cyclehead)->val << endl;
	//printLL(cyclehead);

	Leetcode20 isvalid;
	bool is_valid = isvalid.isValid("{[]}");
	cout <<"{ [] } is "<< is_valid << endl;
	cout << "{{{{{ is "<<isvalid.isValid("{{{{{")<<endl;
	shared_ptr<int> sp1 = make_shared<int>( 10 );
	unique_ptr<int> p1 = make_unique<int>(5);
	shared_ptr<int> p2 = move(p1);
	Leetcode611 findTriNum;
	vector<int> Tri_Array{ 2,2,3,4 };
	cout << "In array 2,2,3,4, there are " << findTriNum.triangleNumber(Tri_Array) << " triangles"<<endl;
	Leetcode26 REMOVEDUP;
	vector<int> arr_removedup{ 0,0,1,2,2,3,3 };
	cout << "0,0,1,2,2,3,3,After remove duplicates: " << REMOVEDUP.removeDuplicates(arr_removedup) << endl;
	topk findtopk;
	vector<int> TOPK{ 3,2,1 };
	cout << "topk nums are " << findtopk.getLeastNumbers_heap(TOPK, 2)<<endl;
	vector<int> topK_fre{ 1,1,1,2,2,3 };
	cout << "Frequency top: " << findtopk.topk_Frequent(topK_fre, 2) << endl;
	vector<int> QS{5, 4, 3, 2, 1};
	cout << "Before Quick Sort: " << QS <<endl;
	SortAlgorithm qs;
	qs.qSort(QS);
	cout <<"After Quick Sort : "<< QS << endl;

	Mystack ms;
	ms.push(1);
	ms.push(2);
	ms.push(3);
	cout << "top of the stack: " << ms.top()<<endl;

	MyQueue mq;
	mq.push(1);
	mq.push(2);
	mq.push(3);
	cout << "top of the queue: " << mq.peek()<<endl;

	MyCircularQueue circularQueue(3);
	circularQueue.enQueue(1);
	circularQueue.enQueue(2);
	circularQueue.enQueue(3); 
	circularQueue.enQueue(4); 
	cout << "Rear element: "<<circularQueue.Rear()<<endl; 
	circularQueue.isFull();
	circularQueue.deQueue();
	circularQueue.enQueue(4);
	circularQueue.Rear(); 
	cout << "Rear element: " << circularQueue.Rear()<<endl;

	SinglyLinkedList repeated{ 1,1,1,2,2,3,3,4,4 };
	Leetcode83 RemoveRepeated;
	printLL(RemoveRepeated.deleteDuplicates(repeated.head));

	vector<int> s{ 1,1,1,2,2,3,3,4,4 };
	Leetcode384 sol = Leetcode384{ s };
	cout << "After shuffle: "<<sol.shuffle()<<endl;
	cout << "Original is: " << sol.reset() << endl;

	/*******************判断字典序*******************/
	int i = 0x11223344;
	char* p;

	p = (char*)&i;
	cout << *p<<endl;
	if (*p == 0x44) {
		printf("Little endian\n");
	}
	else {
		printf("Big endian\n");
	}
	/*******************判断字典序*******************/

	offer67 strint;
	cout << strint.strToInt("     -100") << endl;

	split Split;
	cout << Split.Split("       313413,   34324,,,,,-12432", ',')<<endl;
	//string tryStr { "hello" };
	//for (auto i : tryStr) {
	//	cout << i;
	//}

	MinMaxStack minmaxstack;
	minmaxstack.push(1);
	minmaxstack.push(5);
	minmaxstack.push(6);
	minmaxstack.push(2);
	cout << "max of stack: " << minmaxstack.getMax() << endl;
	cout << "min of stack: " << minmaxstack.getMin() << endl;
	cout << endl;
	MinStack_optimal minstack_opt;
	minstack_opt.push(2);
	minstack_opt.push(1);
	minstack_opt.push(3);
	minstack_opt.push(0);
	//minstack_opt.pop();
	minstack_opt.pop();
	cout << "min of Optimal stack: " << minstack_opt.getMin() << endl;
	cout << "max of Optimal stack: " << minstack_opt.getMax() << endl;
	cout << "top of the Optimanl stack: "<<minstack_opt.top()<<endl;

	Distribute_candy Candy;
	vector<int> d_candy{ 1,0,2 };
	cout << "Distribute candy according to the ratings: " << Candy.candy(d_candy) << endl;

	cout << "gcd of 35 and 28: " << gcd(35, 28) << endl;

	//construct binary tree:
	TreeNode* root = new TreeNode(5);
	TreeNode* root_left = new TreeNode(4);
	TreeNode* root_right = new TreeNode(6);
	TreeNode* root_left_left = new TreeNode(1);
	TreeNode* root_left_right = new TreeNode(2);
	root->left = root_left;
	root->right = root_right;
	root_left->left = root_left_left;
	root_left->right = root_left_right;
	preorder Pre;
	cout << "Pre order is: " << Pre.preorder_iterative(root) << endl;
	postorder Post;
	cout << "Post order is: " << Post.postorder_iterative(root) << endl;
	inorder in;
	cout << "in order is: " << in.inorder_iterative(root) << endl;
	levelorder Level;
	zlevelorder zlevel;
	cout << "level order is: " << endl;
	for (auto const& i : Level.LevelOrder(root)) {
		cout << i<<endl;
	}
	cout << "Z-level order is: " << endl;
	for (auto const& i : zlevel.zlevel(root)) {
		cout << i << endl;
	}
	//rank!
	//vector<int> ints;
	//int player;
	//int num_of_player;
	//cout << "plz input the number of the player: ";
	//cin >> num_of_player;
	//while (num_of_player>0) {
	//	cin >> player;
	//	ints.push_back(player);
	//	--num_of_player;
	//}
	//topk sortrank;
	//cout << sortrank.getLeastNumbers_heap(ints, 3) << endl;
	//vector<int> rank_res = sortrank.getLeastNumbers_heap(ints, 3);
	//cout << rank_res;
	//List l(3);
	//l.traverseList();
	
	char ch[]{ 'M','A','X','H','U','B' };
	char ch1[6]{ 'M','A','X','H','U','B' };
	char ch2[] = "MAXHUB";
	cout << sizeof(ch) << "," << strlen(ch) << endl;
	cout << sizeof(ch1) << "," << strlen(ch1) << endl;
	cout << sizeof(ch2) << "," << strlen(ch2) << endl;

	string str = "night";
	//char* const p_str = str.c_str(); error
	//p_str[0] = 'h';
	cout << str << endl;

	char maxhub[] = "maxhub\0\0\x11\\";
	cout << sizeof(maxhub) << "," << strlen(maxhub) << "," << sizeof(maxhub + 1) << endl;
	char str_[]={ 'h','e','l','l','o' };
	str_[0] = 'a';//ok
	string str2(str_);//ok

	char str__[] = "hello";
	str__[0] = 'a';

	//char *str___ = "hello";//error

	shared_ptr<int> pp1(new int(2));
	shared_ptr<int> pp2(new int(2));
	weak_ptr<int> pp3;
	pp3 = pp1;
	auto pp4 = Copy(pp2);
	cout << pp1.use_count() << "," << pp2.use_count() << "," << pp3.use_count() << "," << pp4.use_count() << endl;

	//int aa[5];
	//*(2 + aa) = 1;

	//char str____[10];
	//cin >> str____;
	//for (auto i : str____) {
	//	cout << i;
	//}
	//map<int, list<pair<int, list<course*> >*> > DB1;
	//for (auto i : DB1) {
	//	for (auto j : i.second) {
	//		for (auto h : j->second) {

	//		}
	//	}
	//}

	//map<int, map<int, list<course*>*>> DB2;
	//for (auto i : DB2) {
	//	for (auto j : i.second) {
	//		for (auto h :*j.second) {
	//			for (auto p : h) {

	//			}

	//		}

	//	}
	//}
	//map<list<string>*, int >m1;
	//for (auto i : m1) {
	//	for(auto j:*i.first)
	//}

	LCS lcs;
	cout << "Longest Common Subsequence: "<<lcs.longestCommonSubsequence("abcde", "ace")<<endl;
	cout << "Longest Common Substring: " << lcs.LongestCommonSubstring("abcde", "abce") << endl;
	string s1 = "hello,world,james";
	string s2 = "james is saying hello";
	cout << "Longest Common Substring: ";
	lcs.printLCString(s1, s2);
	
	
	LRUCache cache(2);
	cache.put(1, 1);
	cache.put(2, 2);
	cout<<"cache get: "<<cache.get(1)<<endl;       // 返回  1
	cache.put(3, 3);    // 该操作会使得密钥 2 作废
	cout << "cache get: " << cache.get(2)<<endl;       // 返回 -1 (未找到)
	cache.put(4, 4);    // 该操作会使得密钥 1 作废
	cache.get(1);       // 返回 -1 (未找到)
	cache.get(3);       // 返回  3
	cache.get(4);       // 返回  4

	vector<int> major_element{ 1, 2, 3, 2, 2, 2, 5, 4, 2 };
	MoreThanHalf mth;
	cout << "more than half element: " << mth.major_element(major_element) << endl;
	cout << "more than half element: " << mth.major_element_vote(major_element) << endl;

	sortLinkedList sortLL;
	SinglyLinkedList selection{ 4,3,2,1 };
	ListNode* newSelectionHead = sortLL.selectSortList(selection.head);
	printLL(newSelectionHead);
	SinglyLinkedList quickSort{ 3,1,4,2 };
	ListNode* newquickSortSwap_Head = sortLL.quickSortList(quickSort.head);
	printLL(newquickSortSwap_Head);
	
	AddtwoNumber add;
	cout << "add two num -8 and 9: " << add.add(-8, 9) << endl;

	vector<int> tryvector{ 1 };
	cout << "sizeof vector is: " << sizeof(tryvector) << endl;

	medianFinder median;
	median.addNum(41);
	median.addNum(35);
	median.addNum(62);
	median.addNum(5);
	median.addNum(97);
	median.addNum(108);
	cout << "median is: " << median.findMedian() << endl;

	trappingRainWater trap;
	vector<int> _trap{ 0,1,0,2,1,0,1,3,2,1,2,1 };
	cout << "Rain water: " << trap.trap(_trap) << endl;

	LongestSubstringLength Lsl;
	cout << "Longest Subtring Length: " << Lsl.LengthofLongestSubstring("abcabcbb") << endl;

	SinglyLinkedList reverseK{ 1,2,3,4,5,6,7 };
	ReverseKGroup reverseKGrp;
	ListNode* newReverseKGroupHEAD = reverseKGrp.reverseKGroup(reverseK.head,2);
	cout << "1,2,3,4,5,6,7 reverse in group of 2 is: ";
	printLL(newReverseKGroupHEAD);
	cout << endl;

	vector<int> stock_array{ 7,1,5,3,6,4 };
	BuyStock stock;
	cout << "maxProfit of multiple transaction is:  "<<stock.maxProfit(stock_array) << endl;

	vector<int> twosum_array{ 2, 7, 11, 15 };
	two_sum twoSum;
	cout <<"two sum subscript: "<< twoSum.twosum(twosum_array,9) << endl;

	vector<int> threesum_array{ -1, 0, 1, 2, -1, -4 };
	three_sum threesum;
	cout << "three sum: " << endl;
	for (auto i : threesum.threesum(threesum_array)) {
		cout << i;
	}
	cout << endl;

	TreeNode* RightSideViewRoot = new TreeNode(1);
	TreeNode* RightSideViewRoot_left = new TreeNode(2);
	TreeNode* RightSideViewRoot_right = new TreeNode(3);
	TreeNode* RightSideViewRoot_left_right = new TreeNode(5);
	TreeNode* RightSideViewRoot_right_right = new TreeNode(4);
	RightSideViewRoot->left = RightSideViewRoot_left;
	RightSideViewRoot->right = RightSideViewRoot_right;
	RightSideViewRoot_left->right = RightSideViewRoot_left_right;
	RightSideViewRoot_right->right = RightSideViewRoot_right_right;
	RightSide rightside;
	cout << "Right side view is: "<<rightside.rightSideView(RightSideViewRoot) << endl;
	GetDepth getdepth;
	cout << "depth of binary tree: " << getdepth.maxdepth(RightSideViewRoot) << endl;
	isBinaryTreeBalanced isbalanced;
	cout << "balanced tree?: " << isbalanced.isbalanced(RightSideViewRoot) << endl;

	maximum_subArray maxsum_subarray;
	vector<int> max_subarray{ -2,1,-3,4,-1,2,1,-5,4 };
	cout << "maxsum of subarray: "<<maxsum_subarray.maxSubArray_Greedy(max_subarray) << endl;

	LongestIncreasingSubsequence LIS;
	vector<int> LongestIS{ 10,9,2,5,3,7,101 };
	cout << "Length of Increasing subseq: " << LIS.lengthofLIS(LongestIS) << endl;

	int A[3][5]{ {1,2,3,4,5},{6,7,8,9,10}, {11,12,13,14,15} };

	cout << A[1][3] << " " << *(A[1] + 3) << " " << *(*(A + 1) + 3) << " "
		<< *(&A[0][0] + 5 * 1 + 3) <<" "<<*(*(A+1))<< endl;
	//char arr[] = "abcd";
	//char arr2[] = "abcd";

	//const char arr3[] = "abcd";
	//const char arr4[] = "abcd";

	///*char* arr7 = "abcd";
	//char* arr8 = "abcd";*/

	//const char* arr7 = "abcd";
	//const char* arr8 = "abcd";

	///*cout << (arr == arr2) << endl;*/
	//cout << (arr3 == arr4) << endl;
	//cout << (arr7 == arr7) << endl;
	//cout << (arr7 == arr8) << endl;

	reversewords WORDS;
	cout << WORDS.reverseWords("i love u") << endl;
}
