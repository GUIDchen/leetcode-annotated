// 题目：1891. 割绳子（Cutting Ribbons）
// 思路：答案具有单调性——若长度 L 能切出 k 段，则更短的也能；于是对长度做「最大化」的二分，判定时统计每条丝带能切出多少段 mid 并求和。
// 时间复杂度：O(n log maxRibbon)，每次判定扫一遍数组；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxLength(vector<int>& ribbons, int k) {  // ribbons：各条丝带长度；k：需要的段数，返回能切出的最长等长段长度
        int left = 0, right = *max_element(ribbons.begin(), ribbons.end());  // 二分区间 [0, 最长丝带]；下界 0 表示可能一段都切不出
        while (left < right) {  // 区间非空时继续二分（闭区间写法，循环结束 left == right 即答案）
            int mid = (left + right + 1) >> 1;  // 取上取整中点，配合下面的 left = mid 避免死循环
            int cnt = 0;  // cnt 累计当前长度 mid 能切出的总段数
            for (int ribbon : ribbons) {  // 逐条丝带统计
                cnt += ribbon / mid;  // 每条可切出 ribbon / mid 段（整除向下取整）
            }  // 结束逐条统计
            if (cnt >= k) {  // 段数够用，说明 mid 可行，答案不小于 mid
                left = mid;  // 收缩到右半区间，保留 mid
            } else {  // 段数不够，mid 偏大
                right = mid - 1;  // 答案严格小于 mid
            }  // 结束分支
        }  // 结束二分
        return left;  // left == right，就是能切出 k 段的最大长度
    }  // 方法结束
};  // 类定义结束