// 题目：2967. 使数组成为等数数组的最小代价（Minimum Cost to Make Array Equalindromic）
// 思路：预处理出 10 位以内的所有回文数并排序（共 2*10^5 个），取出数组的中位数，答案只可能在它左右最近的候选回文数中，逐个算总绝对差取最小。
// 时间复杂度：预处理 O(2*10^5 log 2*10^5) 只做一次，每次调用 O(n log n + log 2*10^5 + n)；空间复杂度：O(2*10^5)，全局回文数表。
using ll = long long;  // 类型别名：ll 表示 64 位整数，代价求和会超过 int 范围

ll ps[2 * 100000];  // 全局数组：预先存放所有 10 位以内的回文数，共 2*100000 个

int init = [] {  // 静态初始化 lambda：程序启动时立刻执行，负责建好回文数表
    for (int i = 1; i <= 100000; i++) {  // 枚举回文的「前缀」 i，用它拼出偶数位与奇数位两种回文
        string s = to_string(i);  // 前缀转成字符串，方便做反转与拼接
        string t1 = s;  // t1 将与 s 拼成偶数位回文（例如 12 -> 1221）
        reverse(t1.begin(), t1.end());  // 反转 s 得到它的倒序
        string t2 = s.substr(0, s.length() - 1);  // t2 去掉 s 的最后一位再反转，用于拼奇数位回文（例如 12 -> 121）
        reverse(t2.begin(), t2.end());  // 反转得到奇数位回文的后半段
        ps[2 * i - 2] = stoll(s + t1);  // 偶数位回文：s + 反转(s)，放在数组第 2i-2 个位置
        ps[2 * i - 1] = stoll(s + t2);  // 奇数位回文：s + 反转(s 去掉最后一位)，放在第 2i-1 个位置
    }  // 前缀枚举结束
    sort(ps, ps + 2 * 100000);  // 所有回文数按数值升序排列，便于后面二分查找
    return 0;  // lambda 的返回值，仅仅为了让它在静态初始化阶段产生副作用
}();  // 立即调用 lambda，完成建表并把结果赋值给 init

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long minimumCost(vector<int>& nums) {  // nums：输入数组；把数组所有元素都改成同一个回文数，返回最小总代价
        sort(nums.begin(), nums.end());  // 先排序，方便取中位数；最优目标值就在中位数附近的回文数中
        int i = lower_bound(ps, ps + 2 * 100000, nums[nums.size() / 2]) - ps;  // 找到第一个不小于中位数的回文数下标 i，答案只可能在它左右各一个候选里
        auto f = [&](ll x) {  // 计算把数组全部改成 x 的总代价
            ll ans = 0;  // 总代价累加器
            for (int& v : nums) {  // 遍历每个元素（用引用避免拷贝）
                ans += abs(v - x);  // 累加绝对差，即把这个元素改成 x 的成本
            }  // for 结束
            return ans;  // 返回总代价
        };  // lambda 结束
        ll ans = LLONG_MAX;  // 用 long long 的最大值初始化答案，保证后续 min 一定能把答案更新掉
        for (int j = i - 1; j <= i + 1; j++) {  // 只需检查中位数左侧、它本身、右侧三个候选回文数
            if (0 <= j && j < 2 * 100000) {  // 下标越界保护：候选下标必须落在回文数表范围内
                ans = min(ans, f(ps[j]));  // 用该候选回文数的总代价更新最优解
            }  // if 结束
        }  // for 结束
        return ans;  // 返回最小总代价
    }  // 方法结束
};  // 类定义结束