// 题目：1231. 分享巧克力（Divide Chocolate）
// 思路：二分答案 + 贪心校验。答案（最小块的甜度）具有单调性：下限越高越难切够 k+1 块；对候选下限贪心从前往后切，能切出超过 k 块即说明该下限可行。
// 时间复杂度：O(n log S)，S 为甜度总和，每次校验扫一遍数组；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 方法对外可见
    int maximizeSweetness(vector<int>& sweetness, int k) {  // sweetness：每块巧克力的甜度；k：人数（要切成 k+1 块），返回「最小块的最大可能甜度」
        int l = 0, r = accumulate(sweetness.begin(), sweetness.end(), 0);  // 二分下界 l = 0，上界 r 取整条巧克力的甜度总和（答案不可能更大）
        auto check = [&](int x) {  // 校验函数：假设每块至少要有 x 的甜度，看能否切出多于 k 块
            int s = 0, cnt = 0;  // s：当前正在累积的这一块已攒到的甜度；cnt：已经切好的块数
            for (int v : sweetness) {  // 按顺序贪心切分，越早凑够 x 就切，剩下的留给后面的块
                s += v;  // 把当前这块的甜度累加进来
                if (s >= x) {  // 攒够 x 就立即切下这一块
                    s = 0;  // 切完从 0 重新开始累积
                    ++cnt;  // 切好的块数加 1
                }  // 结束这一块的处理
            }  // 结束对甜度数组的遍历
            return cnt > k;  // 能切出超过 k 块（即至少 k+1 块）说明下限 x 可行
        };  // lambda 校验函数定义结束
        while (l < r) {  // 在单调的答案区间上二分，找最大的可行 x
            int mid = (l + r + 1) >> 1;  // 取上中位数，保证 mid > l，避免 l == mid 时死循环
            if (check(mid)) {  // x 可行，答案至少是 mid
                l = mid;  // 把下界抬上来缩小范围
            } else {  // x 不可行，说明下限取高了
                r = mid - 1;  // 答案落在左半区间，把上界降下来
            }  // 结束二分分支
        }  // 结束二分循环
        return l;  // 循环结束时 l == r，就是最大的可行下限
    }  // 方法结束
};  // 类定义结束