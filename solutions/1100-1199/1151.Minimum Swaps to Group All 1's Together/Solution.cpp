// 题目：1151. 最少交换次数来组合所有的 1（Minimum Swaps to Group All 1's Together）
// 思路：最终连续 1 的窗口长度固定为 1 的总个数 k，滑动窗口统计窗口内 1 的最大个数 mx，答案就是 k - mx（窗口内 0 的个数）。
// 时间复杂度：O(n)，一次计数加一次滑动；空间复杂度：O(1)，只用常数个额外变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minSwaps(vector<int>& data) {  // data 只含 0 和 1；k 将作为窗口长度
        int k = 0;  // k 记录 1 的总个数
        for (int& v : data) {  // 遍历每个元素
            k += v;  // 累加得到 1 的总数
        }  // 循环结束
        int t = 0;  // t 记录当前窗口内 1 的个数
        for (int i = 0; i < k; ++i) {  // 初始化第一个长度为 k 的窗口
            t += data[i];  // 把前 k 个元素累加进来
        }  // 第一个窗口统计完成
        int mx = t;  // mx 记录所有窗口中最多的 1 的个数
        for (int i = k; i < data.size(); ++i) {  // 窗口右移：每次去掉左端一个、加入右端一个
            t += data[i];  // 纳入新进入窗口的元素
            t -= data[i - k];  // 移除离开窗口的元素
            mx = max(mx, t);  // 更新窗口内 1 的最大值
        }  // 滑动结束
        return k - mx;  // 窗口内 0 的个数就是最少需要的交换次数
    }  // 方法结束
};  // 类定义结束