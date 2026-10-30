// 3766. 将数字变成二进制回文数的最少操作 / Minimum Operations to Make Binary Palindrome
// 核心思路：预处理 14 位以内的所有二进制回文数并保持升序，对每个 nums[k] 二分查找左右相邻的两个回文数，取最近距离。
// 复杂度：时间 O(2^14 + n log 2^14)，空间 O(2^14)。
vector<int> p;  // 全局有序表，存放所有二进制回文数

auto init = [] {  // 用 lambda 在程序启动前完成一次性预处理
    int N = 1 << 14;  // 枚举范围 2^14
    for (int i = 0; i < N; ++i) {  // 逐个枚举 0..2^14-1
        string s = bitset<14>(i).to_string();  // 取该数的 14 位二进制串
        s = s.substr(s.find_first_not_of('0') == string::npos ? 13 : s.find_first_not_of('0'));  // 去掉前导零，全零时保留最后一位
        string rs = s;  // 复制一份用于反转
        reverse(rs.begin(), rs.end());  // 反转得到镜像串
        if (s == rs) {  // 与原串相同即为回文
            p.push_back(i);  // 记录该回文数
        }
    }
    return 0;  // lambda 的返回值，仅用于满足静态初始化
}();

class Solution {  // 定义解法类
public:  // 公有方法区
    vector<int> minOperations(vector<int>& nums) {  // 对每个 nums[k] 求变成二进制回文数的最少操作数
        int n = nums.size();  // 元素个数
        vector<int> ans(n, INT_MAX);  // 答案数组，先初始化为极大值
        for (int k = 0; k < n; ++k) {  // 逐个处理每个数
            int x = nums[k];  // 当前数值
            int i = lower_bound(p.begin(), p.end(), x) - p.begin();  // 二分找到第一个大于等于 x 的回文数下标
            if (i < (int) p.size()) {  // 右侧存在候选回文数
                ans[k] = min(ans[k], p[i] - x);  // 用右侧回文数更新最小操作数
            }
            if (i >= 1) {  // 左侧存在候选回文数
                ans[k] = min(ans[k], x - p[i - 1]);  // 用左侧回文数更新最小操作数
            }
        }
        return ans;  // 返回每个数的最少操作数
    }  // 方法结束
};  // 类结束
