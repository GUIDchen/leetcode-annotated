// 3591. 检查元素频次是否为质数（Check if Any Element Has Prime Frequency）
// 核心思路：用哈希表统计每个元素的出现次数，再对每个频次做试除质数判定；命中任一质数频次即返回 true。
// 复杂度：时间 O(n + U·√n)，空间 O(U)，其中 U 为不同元素的个数。
class Solution {  // 主解类
public:  // 对外接口
    bool checkPrimeFrequency(vector<int>& nums) {  // 判断数组中是否存在出现次数为质数的元素
        unordered_map<int, int> cnt;  // 哈希表：元素 -> 出现次数
        for (int x : nums) {  // 遍历数组中的每个元素
            ++cnt[x];  // 对应元素的计数加一
        }  // 循环结束

        for (auto& [_, x] : cnt) {  // 遍历每个元素及其频次
            if (isPrime(x)) {  // 该频次是质数
                return true;  // 只要有一个满足就返回真
            }  // if 结束
        }  // 循环结束
        return false;  // 没有任何质数频次
    }  // checkPrimeFrequency 结束

private:  // 内部辅助函数
    bool isPrime(int x) {  // 判断 x 是否为质数
        if (x < 2) {  // 小于 2 的数不是质数
            return false;  // 返回假
        }  // if 结束
        for (int i = 2; i <= x / i; ++i) {  // 只需试除到 sqrt(x)，避免溢出写成 i <= x / i
            if (x % i == 0) {  // 发现因子
                return false;  // 不是质数
            }  // if 结束
        }  // 循环结束
        return true;  // 没有因子，是质数
    }  // isPrime 结束
};  // 类定义结束
