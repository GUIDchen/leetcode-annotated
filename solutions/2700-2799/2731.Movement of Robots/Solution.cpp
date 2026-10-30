// 题目：2731. 移动机器人（Movement of Robots）
// 思路：机器人相撞等价于互相穿过，先算出每个机器人的最终坐标并排序，再用前缀和求所有点对距离之和。
// 时间复杂度：O(n log n)，主要是排序；空间复杂度：O(n)，存放最终坐标。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int sumDistance(vector<int>& nums, string s, int d) {  // nums 是初始坐标，s 是方向串，d 是移动秒数
        int n = nums.size();  // 机器人数量
        vector<long long> arr(n);  // 用 64 位整数保存每个机器人移动 d 秒后的最终坐标
        for (int i = 0; i < n; ++i) {  // 逐个计算机器人的最终坐标
            arr[i] = 1LL * nums[i] + (s[i] == 'L' ? -d : d);  // 初始坐标 nums[i]：向左走减 d，向右走加 d
        }
        sort(arr.begin(), arr.end());  // 排序后才能按位置顺序线性地统计点对距离
        long long ans = 0;  // 所有点对距离之和
        long long sum = 0;  // 前缀和：前面所有已处理坐标的总和
        const int mod = 1e9 + 7;  // 取模常量
        for (int i = 0; i < n; ++i) {  // 排序后从小到大遍历，每个点只需与它左边的所有点算距离
            ans = (ans + i * arr[i] - sum) % mod;  // arr[i] 与左侧 i 个点的距离和 = i*arr[i] - 前缀和
            sum += arr[i];  // 把当前坐标并入前缀和，供后面的点使用
        }
        return ans;  // 返回所有点对距离之和
    }
};