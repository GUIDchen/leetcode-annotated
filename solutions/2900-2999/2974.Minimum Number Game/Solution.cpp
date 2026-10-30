// 题目：2974. 最小数字游戏（Minimum Number Game）
// 思路：用最小堆模拟游戏，每轮弹出最小的两个数，按题意 Bob 拿较小的、Alice 拿较大的，依次放入结果。
// 时间复杂度：O(n log n)，建堆 O(n)、共 n/2 轮弹出；空间复杂度：O(n)，堆与答案数组各存 n 个数。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> numberGame(vector<int>& nums) {  // nums：输入数组，返回按游戏规则重排后的数组
        priority_queue<int, vector<int>, greater<int>> pq;  // 小根堆：greater<int> 让堆顶始终是最小值，便于每轮取最小数
        for (int x : nums) {  // 把数组里的每个数字依次放进堆
            pq.push(x);  // 入堆后堆内自动维护有序，堆顶即当前最小值
        }  // for 循环结束，所有数字都已入堆
        vector<int> ans;  // 结果数组：按 Bob、Alice 的顺序追加每轮取走的数
        while (pq.size()) {  // 堆非空就继续一轮，每轮恰好消耗两个数
            int a = pq.top();  // a 是本轮最小的数，按题意归 Alice
            pq.pop();  // 弹出堆顶，让下一个最小值浮上来
            int b = pq.top();  // b 是剩余数字中的最小值，按题意归 Bob
            pq.pop();  // 同样弹出堆顶，完成本轮取数
            ans.push_back(b);  // Bob 先把他拿到的 b 放入结果
            ans.push_back(a);  // 再放 Alice 拿到的 a，于是每两个数在结果里交换了顺序
        }  // while 循环结束，堆已清空
        return ans;  // 返回最终排列
    }  // 方法结束
};  // 类定义结束