// 题目：2035. 将数组分成两个数组并最小化数组和的差（Partition Array Into Two Arrays to Minimize Sum Difference）
// 思路：折半枚举。把数组切成前后各 n=len/2 个元素，枚举前一半的每个子集，用 s 记录「选中元素之和 - 未选元素之和」，并按选中个数 cnt 分类存到 f；后一半同法得到 g。
//       两半各自贡献一半的符号，把 f[k] 与 g[n-k] 配对后，用 f[k] + g[n-k] 表示两组和的差；对 g[n-k] 排序后二分查找最接近 -a 的值，取绝对值最小的差即为答案。
// 时间复杂度：O(2^(n/2) * n + 2^(n/2) * log(2^(n/2)))，即 O(n·2^(n/2))，n 为原数组长度；空间复杂度：O(2^(n/2))，两半的子集和都要存下来。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimumDifference(vector<int>& nums) {  // nums 是长度为偶数（2n）的输入数组，要求分成两个长度相等的数组
        int n = nums.size() >> 1;  // 折半长度 n：原数组长度是 2n
        vector<vector<int>> f(n + 1), g(n + 1);  // f[k]/g[k] 分别保存前一半/后一半中「恰好选 k 个」时的 (选中和 - 未选和)
        for (int i = 0; i < (1 << n); ++i) {  // 枚举前一半的全部子集，用 n 位二进制掩码表示每个元素选或不选
            int s = 0, cnt = 0;  // s 是前一半的符号和（选为 +，不选为 -），cnt 是选中个数
            int s1 = 0, cnt1 = 0;  // s1/cnt1 是后一半同一位掩码对应的符号和与选中个数
            for (int j = 0; j < n; ++j) {  // 逐位遍历前一半的 n 个元素
                if (i & (1 << j)) {  // 第 j 位为 1 表示该元素被分到第一组
                    s += nums[j];  // 前一半第 j 个元素计入正贡献
                    ++cnt;  // 前一半选中个数加一
                    s1 += nums[n + j];  // 后一半同一位也按「选中」处理，保证两半选取个数一致
                    ++cnt1;  // 后一半选中个数加一
                } else {  // 第 j 位为 0 表示该元素被分到第二组
                    s -= nums[j];  // 前一半第 j 个元素计入负贡献
                    s1 -= nums[n + j];  // 后一半同一位也按「未选」处理
                }  // 结束选/不选分支
            }  // 结束逐位枚举
            f[cnt].push_back(s);  // 把该子集的前一半符号和按「选中个数」归档
            g[cnt1].push_back(s1);  // 把对应后一半符号和按「选中个数」归档
        }  // 结束子集枚举
        for (int i = 0; i <= n; ++i) {  // 对每一组的符号和排序，为二分查找做准备
            sort(f[i].begin(), f[i].end());  // f[i] 升序，便于后续二分
            sort(g[i].begin(), g[i].end());  // g[i] 同样升序
        }  // 结束排序
        int ans = INT_MAX;  // 答案初始化为最大整数，后面不断取更小的差
        for (int i = 0; i <= n; ++i) {  // 枚举前一半选中 i 个元素的情形
            for (int a : f[i]) {  // 枚举 f[i] 中的每一个符号和 a
                int left = 0, right = g[n - i].size() - 1;  // 在 g[n-i] 上二分：left/right 为闭区间端点（总选中数应为 n）
                int b = -a;  // 寻找使 a + b 尽量接近 0 的 b，即 b ≈ -a
                while (left < right) {  // 二分寻找第一个 g[n-i][mid] >= b 的位置
                    int mid = (left + right) >> 1;  // 取中点（右移一位等价于整除 2）
                    if (g[n - i][mid] >= b)  // 中点值已经够大，答案位置不会在它右边
                        right = mid;  // 收缩右边界
                    else  // 否则中点太小
                        left = mid + 1;  // 收缩左边界
                }  // 结束二分
                ans = min(ans, abs(a + g[n - i][left]));  // 用二分落点的值更新答案（两组和的差取绝对值）
                if (left > 0) ans = min(ans, abs(a + g[n - i][left - 1]));  // 也要检查落点左边一个：最接近 -a 的值可能在其左侧
            }  // 结束 f[i] 枚举
        }  // 结束选中个数枚举
        return ans;  // 返回最小的两组和的差
    }  // 结束 minimumDifference
};  // 结束 Solution 类