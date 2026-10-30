// 题目：2530. 执行 K 次操作后的最大分数（Maximal Score After Applying K Operations）
// 核心思路：贪心 + 大根堆。每次取出当前最大值计入得分，再把它替换成 ⌈v / 3⌉ 放回堆中，重复 k 次。
// 时间复杂度：O(n + k log n)，建堆 O(n)、每次取顶与入堆 O(log n)；空间复杂度：O(n)，堆中存 n 个数。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long maxKelements(vector<int>& nums, int k) {  // nums 为初始数组，k 为操作次数，返回累计得到的最大分数
        priority_queue<int> pq(nums.begin(), nums.end());  // 默认大根堆：堆顶永远是当前最大的数
        long long ans = 0;  // 累计得分，用 long long 防止多次加法后溢出 int
        while (k--) {  // 执行 k 次操作：k 每次先判断再自减
            int v = pq.top();  // 取出当前最大值，它一定是最该被加进得分的数
            pq.pop();  // 弹出堆顶，准备用缩减后的值替换它
            ans += v;  // 把这个最大值累加进总分
            pq.push((v + 2) / 3);  // 向上取整 v/3：整数除法加 2 再除 3 即可实现 ceil
        }  // k 次操作完成
        return ans;  // 返回累计的最大分数
    }  // 方法结束
};  // 类定义结束