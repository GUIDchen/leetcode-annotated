// 题目：2137. 通过倒水操作让所有的水桶所含水量相等（Pour Water Between Buckets to Make Water Levels Equal）
// 思路：二分答案水位 v，统计高于 v 可倒出的水量 a 与低于 v 需补入的水量 b（倒水有 loss% 损耗），a >= b 即 v 可达。
// 时间复杂度：O(n log(r / 1e-5))，二分约 50 次、每次 O(n)；空间复杂度：O(1)。
class Solution {  // LeetCode 约定的题解类
public:
    double equalizeWater(vector<int>& buckets, int loss) {  // buckets：各桶当前水量；loss：倒水过程中的损耗百分比
        double l = 0, r = *max_element(buckets.begin(), buckets.end());  // 二分下界取 0，上界取当前最高水位（答案不会超过最大的那一桶）
        auto check = [&](double v) {  // 判定函数：能否把所有水桶都调到水位 v
            double a = 0, b = 0;  // a 收集富余的水量，b 收集需要补入的水量
            for (int x : buckets) {  // 逐个水桶统计
                if (x > v) {  // 高于目标水位的水桶可以把多余的水倒出去
                    a += x - v;  // 多余部分全部计入可倒出的总量
                } else {  // 不高于目标水位的水桶需要补水
                    b += (v - x) * 100 / (100 - loss);  // 倒水有 loss% 损耗，所以要补 v-x 就得从富余侧多取，按比例放大
                }
            }
            return a >= b;  // 可倒出的水够填缺口（已含损耗）说明水位 v 可行
        };
        while (r - l > 1e-5) {  // 浮点数二分：区间足够小（小于 1e-5）就停止
            double mid = (l + r) / 2;  // 取中点为候选水位
            if (check(mid)) {  // mid 可行，说明答案不小于 mid
                l = mid;  // 抬高下界
            } else {  // mid 不可行，说明答案更小
                r = mid;  // 压低上界
            }
        }
        return l;  // 返回二分收敛后的可行下界
    }
};  // 题解类结束