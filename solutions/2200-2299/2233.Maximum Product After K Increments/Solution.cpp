// 题目：2233. K 次增加后的最大乘积（Maximum Product After K Increments）
// 核心思路：贪心——每次把 1 加到当前最小的元素上，乘积增长最快；
//           用最小堆维护全部元素，重复 k 次后累乘所有元素并对 1e9+7 取模。
// 时间复杂度：O(n + k log n)；空间复杂度：O(n)，堆中存放全部元素。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maximumProduct(vector<int>& nums, int k) {  // nums：初始数组；k：最多增加的次数
        priority_queue<int, vector<int>, greater<int>> pq;  // 小根堆，队首始终是最小元素
        for (int x : nums) {  // 把所有元素放进堆里
            pq.push(x);  // 入堆后堆自动调整，队首保持最小
        }
        while (k-- > 0) {  // 一共做 k 次「把最小值加一」
            int smallest = pq.top();  // 取出当前最小值
            pq.pop();  // 先弹出，才能修改后重新入堆
            pq.push(smallest + 1);  // 加一后放回堆中，维持最小堆性质
        }
        const int mod = 1e9 + 7;  // 题目要求的取模常量
        long long ans = 1;  // 累乘结果，用 long long 避免中间结果溢出
        while (!pq.empty()) {  // 遍历堆中所有元素求乘积
            ans = (ans * pq.top()) % mod;  // 边乘边取模，避免数值过大
            pq.pop();  // 弹出已处理的元素
        }
        return static_cast<int>(ans);  // 取模后一定落在 int 范围内，转换后返回
    }
};
