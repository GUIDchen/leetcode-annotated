// 题目：3556. 最大质数子字符串之和（Sum of Largest Prime Substrings）
// 思路：枚举每个起点并向右滚动累积子串数值，逐个试除判断是否为质数，把质数子串放进集合去重；最后对集合升序排序，从最大值开始累加至多三个不同质数即为答案。
// 时间复杂度：O(n² · √V)，n 为串长、V 为最大子串数值（质数判定试除到 √x）；空间复杂度：O(n²)，集合中最多存放 n(n+1)/2 个不同质数。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long sumOfLargestPrimes(string s) {  // s：数字字符串；返回其中最大的三个不同质数子串之和
        unordered_set<long long> st;  // st：去重存放所有质数子串的数值
        int n = s.size();  // n：字符串长度

        for (int i = 0; i < n; ++i) {  // 枚举子串起点 i
            long long x = 0;  // x：以 i 为起点的子串数值，逐位滚动累积
            for (int j = i; j < n; ++j) {  // 枚举子串终点 j，把子串向右扩展
                x = x * 10 + (s[j] - '0');  // 追加一位数字，形成新的子串数值
                if (is_prime(x)) {  // 当前子串的数值是质数
                    st.insert(x);  // 去重后加入集合
                }  // 质数判断结束
            }  // 该起点的所有子串枚举完毕
        }  // 全部起点枚举完毕

        vector<long long> sorted(st.begin(), st.end());  // 把去重集合转成数组，便于按下标访问
        sort(sorted.begin(), sorted.end());  // 升序排序，最大的质数排在末尾

        long long ans = 0;  // ans：最大的三个不同质数之和
        int cnt = 0;  // cnt：已累加的质数个数
        for (int i = (int) sorted.size() - 1; i >= 0 && cnt < 3; --i, ++cnt) {  // 从最大值开始向前，最多取三个
            ans += sorted[i];  // 逐个累加
        }  // 累加结束
        return ans;  // 返回总和
    }  // 方法结束

private:  // 以下为私有辅助函数
    bool is_prime(long long x) {  // is_prime：判断 x 是否为质数
        if (x < 2) return false;  // 小于 2 的数不是质数
        for (long long i = 2; i * i <= x; ++i) {  // 只需试除到 √x，i*i <= x 避免开方误差
            if (x % i == 0) return false;  // 找到因子，说明不是质数
        }  // 试除结束
        return true;  // 没有因子，是质数
    }  // 辅助函数结束
};  // 类定义结束