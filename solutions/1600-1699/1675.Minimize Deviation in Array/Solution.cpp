// 题目：1675. 数组的最小偏移量（Minimize Deviation in Array）
// 思路：奇数先乘 2 统一成偶数（只能乘一次的环节一次用满），之后不断把最大值除以 2，用大根堆维护最大值并实时更新最小值与答案。
// 时间复杂度：O(n log n · log V)，每个数最多除 log V 次 2，每次堆操作 O(log n)；空间复杂度：O(n)，堆中保存 n 个数。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimumDeviation(vector<int>& nums) {  // nums：输入数组，元素可做乘 2 或除 2（偶数时）操作
        int mi = INT_MAX;  // 记录当前最小值，初值取最大整数
        priority_queue<int> pq;  // 大根堆，堆顶始终是当前最大值
        for (int v : nums) {  // 遍历每个元素，先做预处理
            if (v & 1) v <<= 1;  // 奇数只能乘 2，先乘成偶数，之后只能往小变
            pq.push(v);  // 处理后的值入堆
            mi = min(mi, v);  // 同步维护最小值
        }  // 预处理结束，堆顶是最大值、mi 是最小值
        int ans = pq.top() - mi;  // 初始偏移量 = 最大值 - 最小值
        while (pq.top() % 2 == 0) {  // 只要最大值是偶数，就还能把它缩小
            int x = pq.top() >> 1;  // 取出堆顶并右移一位，相当于除以 2
            pq.pop();  // 弹出原来的最大值
            pq.push(x);  // 把缩小后的值放回堆中
            mi = min(mi, x);  // 缩小后可能产生新的最小值，同步更新
            ans = min(ans, pq.top() - mi);  // 用新的极差更新答案
        }  // 循环结束：堆顶已是奇数，无法继续缩小
        return ans;  // 返回记录到的最小偏移量
    }  // 方法结束
};  // 类定义结束