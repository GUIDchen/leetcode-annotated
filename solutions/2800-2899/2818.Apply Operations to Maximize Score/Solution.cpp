// 题目：2818. 操作使得分最大（Apply Operations to Maximize Score）
// 思路：每个数的「价值」是它的不同质因数个数。先用单调栈求出每个下标 i 作为区间最大值时的作用区间 (left[i], right[i])，可选它 i-l 与 r-i 的所有组合；再按数值从大到小贪心取，用快速幂把价值累乘进答案。
// 时间复杂度：O(n·log V + n·log n)，质因数分解与排序为主；空间复杂度：O(n)，存三元组、左右边界与单调栈。
class Solution {  // 题解类
public:  // 题解方法对外可见
    int maximumScore(vector<int>& nums, int k) {  // nums：输入数组；k：最多能做的操作次数；返回可能得到的最大得分（对 1e9+7 取模）
        const int mod = 1e9 + 7;  // 取模常量，所有乘法都要取模防止溢出
        int n = nums.size();  // 数组长度
        vector<tuple<int, int, int>> arr(n);  // 每项存 (原下标, 质因数个数, 数值)，后续要按原下标回查
        for (int i = 0; i < n; ++i) {  // 预处理每个元素的价值（不同质因数个数）
            arr[i] = {i, primeFactors(nums[i]), nums[i]};  // primeFactors 计算不同质因数个数，nums[i] 保留原值
        }
        vector<int> left(n, -1);  // left[i]：i 左边第一个质因数个数严格更大的下标，-1 表示没有
        vector<int> right(n, n);  // right[i]：i 右边第一个质因数个数大于等于它的下标，n 表示没有
        stack<int> stk;  // 单调栈，保存尚未确定边界的下标
        for (auto [i, f, _] : arr) {  // 从左往右扫描：维护一个质因数个数单调递减的栈
            while (!stk.empty() && get<1>(arr[stk.top()]) < f) {  // 栈顶比当前元素小，说明栈顶的右边界就是当前下标，直接弹出
                stk.pop();  // 弹出栈顶，它的左侧边界在之前已经记录过
            }
            if (!stk.empty()) {  // 弹完后栈顶就是左边第一个质因数个数严格更大的元素
                left[i] = stk.top();  // 记录左边界
            }
            stk.push(i);  // 当前下标入栈，等待右侧元素来结算它的边界
        }
        stk = stack<int>();  // 清空栈，准备从右往左再扫一次求右边界
        for (int i = n - 1; ~i; --i) {  // ~i 等价于 i >= 0，一直遍历到下标 0
            int f = get<1>(arr[i]);  // 当前元素的价值
            while (!stk.empty() && get<1>(arr[stk.top()]) <= f) {  // 注意用 <=：右侧遇到价值相等的元素也要让位，避免同一子数组被重复计数
                stk.pop();  // 弹出栈顶
            }
            if (!stk.empty()) {  // 栈顶就是右边第一个价值大于等于当前的下标
                right[i] = stk.top();  // 记录右边界
            }
            stk.push(i);  // 入栈继续向左扫描
        }
        sort(arr.begin(), arr.end(), [](const auto& lhs, const auto& rhs) {  // 按数值从大到小排序：先处理大的数才能让总乘积最大
            return get<2>(rhs) < get<2>(lhs);  // 比较第 3 项（数值），实现降序
        });
        long long ans = 1;  // 答案从 1 开始做连乘
        auto qpow = [&](long long a, int n) {  // 快速幂：计算 a^n mod mod
            long long ans = 1;  // 局部累乘结果，与外层 ans 区分
            for (; n; n >>= 1) {  // 指数每轮右移一位，相当于除以 2
                if (n & 1) {  // 当前二进制位为 1，需要把这一份底数乘进结果
                    ans = ans * a % mod;  // 累乘并取模
                }
                a = a * a % mod;  // 底数平方，对应指数的下一个二进制位
            }
            return ans;  // 返回 a^n mod mod
        };
        for (auto [i, _, x] : arr) {  // 按数值降序依次取用：下标 i 最多能贡献 (i-l)*(r-i) 次得分
            int l = left[i], r = right[i];  // 取出该下标的左右边界
            long long cnt = 1LL * (i - l) * (r - i);  // 以 i 为区间最大值（价值最大）的连续子数组个数，用 long long 防溢出
            if (cnt <= k) {  // 剩余操作次数足够用完这个数的全部可选次数
                ans = ans * qpow(x, cnt) % mod;  // 把这些次数全部乘进答案
                k -= cnt;  // 扣掉已经用掉的次数
            } else {  // 剩余次数不够，只能再用 k 次，用完即结束
                ans = ans * qpow(x, k) % mod;  // 把剩下的 k 次用完
                break;  // 次数耗尽，后面的数不可能再被选，直接跳出
            }
        }
        return ans;  // 返回最大得分
    }

    int primeFactors(int n) {  // 辅助函数：用试除法求 n 的不同质因数个数
        int i = 2;  // 从最小的质数 2 开始试
        unordered_set<int> ans;  // 用集合去重：同一个质因数只应计一次
        while (i <= n / i) {  // 写成 i <= n/i 而不是 i*i <= n，避免 int 溢出
            while (n % i == 0) {  // 反复除掉当前的质因数 i
                ans.insert(i);  // 记录这个质因数（重复出现也只算一次）
                n /= i;  // 把 i 从 n 中除掉
            }
            ++i;  // 换下一个可能的因数
        }
        if (n > 1) {  // 剩下的 n 本身就是一个大于 sqrt(原 n) 的质因数
            ans.insert(n);  // 把它也计入
        }
        return ans.size();  // 返回不同质因数的个数
    }
};