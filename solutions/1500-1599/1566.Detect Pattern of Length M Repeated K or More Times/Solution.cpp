// 题目：1566. 重复至少 K 次且长度为 M 的模式（Detect Pattern of Length M Repeated K or More Times）
// 思路：比较 arr[i] 与 arr[i-m]，累计连续相等的次数；达到 (k-1)*m 就说明某个长度 m 的模式连续重复了 k 次。
// 时间复杂度：O(n)，n 为数组长度，只做一次线性扫描；空间复杂度：O(1)，只用常数个额外变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool containsPattern(vector<int>& arr, int m, int k) {  // arr：输入数组；m：模式长度；k：最少重复次数
        if (arr.size() < m * k) {  // 总长度不足 m*k 时放不下 k 个长度为 m 的模式
            return false;  // 直接判定不存在
        }
        int cnt = 0, target = (k - 1) * m;  // cnt：当前连续匹配的字符数；target：除首段外需要匹配的字符总数
        for (int i = m; i < arr.size(); ++i) {  // 从下标 m 开始，才能与 i-m 处的字符对应比较
            if (arr[i] == arr[i - m]) {  // 与相距 m 的位置相等，说明模式正在延续
                if (++cnt == target) {  // 先累加，再判断是否已凑够 k 次重复所需的长度
                    return true;  // 找到合法模式
                }
            } else {  // 一旦不相等，模式断裂
                cnt = 0;  // 计数器清零，从后面的位置重新寻找
            }
        }
        return false;  // 扫描结束仍未找到
    }
};
