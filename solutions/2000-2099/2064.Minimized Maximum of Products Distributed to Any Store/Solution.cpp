// 题目：2064. 分配给商店的最多商品的最小值（Minimized Maximum of Products Distributed to Any Store）
// 思路：二分答案，枚举「单个商店最多拿多少件商品」x，贪心地用 ceil(v/x) 家店装完每种商品，商店总数不超过 n 即说明 x 可行。
// 时间复杂度：O(m log 1e5)，m 为商品种类数，每次判定 O(m)；空间复杂度：O(1)，只用了常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimizedMaximum(int n, vector<int>& quantities) {  // n 是商店数量，quantities 是每种商品的件数
        int left = 1, right = 1e5;  // 答案下界是 1（每店至少放一件），上界取题面给出的最大值 1e5
        while (left < right) {  // 在 [left, right] 上二分，逐步收缩到最小的可行上限
            int mid = (left + right) >> 1;  // 右移一位等价于除以 2，得到本次尝试的单店上限
            int cnt = 0;  // 统计按上限 mid 分配时最少需要多少家商店
            for (int& v : quantities) {  // 逐个商品种类累加所需商店数
                cnt += (v + mid - 1) / mid;  // 向上取整：v 件商品每店最多 mid 件，至少需要 ceil(v/mid) 家店
            }
            if (cnt <= n) {  // 商店数量够用，说明 mid 可行，答案可能更小
                right = mid;  // 把 mid 保留为候选答案，收缩右边界
            } else {  // 商店不够用，说明 mid 取得太小
                left = mid + 1;  // 放弃 mid，答案至少是 mid + 1
            }
        }
        return left;  // 区间收敛到一点，left 就是最小的可行上限
    }
};  // 类定义结束