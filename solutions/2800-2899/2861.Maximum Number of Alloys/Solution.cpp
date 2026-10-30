// 题目：2861. 最大合金数（Maximum Number of Alloys）
// 思路：答案具有单调性，二分合金数 mid；对每台机器计算缺口花费，只要有任意一台不超过 budget 就说明 mid 可行。
// 复杂度：时间 O(k·n·log(budget))，二分 log 次、每次检查 k 台机器各 n 种金属；空间 O(1)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxNumberOfAlloys(int n, int k, int budget, vector<vector<int>>& composition, vector<int>& stock, vector<int>& cost) {  // n：金属种类数；k：机器台数；budget：预算；composition/stock/cost：配比、库存、单价
        auto isValid = [&](long long target) {  // 判定函数：能否只用一台机器造出 target 个合金
            for (int i = 0; i < k; i++) {  // 逐一尝试每一台机器
                long long remain = budget;  // 这台机器当前剩余的预算
                auto currMachine = composition[i];  // 取出该机器的金属配比，方便后面逐项访问
                for (int j = 0; j < n && remain >= 0; j++) {  // 遍历每种金属；预算一旦透支就提前结束
                    long long need = max(0LL, target * currMachine[j] - stock[j]);  // 这种金属还缺多少：需求 target 份减去已有库存，负数按 0 算
                    remain -= need * cost[j];  // 缺口乘单价，从预算里扣掉
                }
                if (remain >= 0) {  // 预算没透支完，说明这台机器能造出 target 个
                    return true;  // 直接返回可行
                }
            }
            return false;  // 所有机器都买不起，说明 target 不可达
        };
        long long l = 0, r = budget + stock[0];  // 二分上界取 budget + stock[0]：再多也买不起任何额外金属
        while (l < r) {  // 二分查找最大可行的合金数
            long long mid = (l + r + 1) >> 1;  // 取上中位数，保证区间一定收缩
            if (isValid(mid)) {  // mid 可行，把下界抬上来继续找更大的
                l = mid;  // 记录左边界为可行解
            } else {  // 否则可行区间落在左半边
                r = mid - 1;  // 上界下调到 mid - 1
            }
        }
        return l;  // 循环结束时 l 就是最大可行的合金数
    }
};