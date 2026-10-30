// 题目：2517. 礼盒的最大甜蜜度（Maximum Tastiness of Candy Basket）
// 核心思路：二分答案。先排序，再对候选甜蜜度 x 贪心验证：价格差达到 x 就选，最多能选够 k 个则 x 可行，二分出最大可行值。
// 时间复杂度：O(n log n + n log V)，V 为价格跨度；空间复杂度：O(1)，除排序外只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解接口对外可见
    int maximumTastiness(vector<int>& price, int k) {  // price：糖果价格数组；k：礼盒中要装的糖果数量
        sort(price.begin(), price.end());  // 先升序排序，便于之后按价格顺序贪心选取
        int l = 0, r = price.back() - price[0];  // 答案区间：甜蜜度最小为 0，最大为最大值与最小值之差
        auto check = [&](int x) -> bool {  // check(x)：判断甜蜜度至少为 x 时能否选出 k 个糖果
            int cnt = 0, pre = -x;  // cnt 记录已选个数；pre 置为 -x，保证第一个糖果必定被选中
            for (int& cur : price) {  // 按价格从小到大依次尝试每个糖果
                if (cur - pre >= x) {  // 与上一个选中价格相差至少 x，选它不会让甜蜜度低于 x
                    pre = cur;  // 更新上一个被选中糖果的价格
                    ++cnt;  // 选中个数加一
                }  // 结束 if
            }  // 结束 for，一轮贪心选取完成
            return cnt >= k;  // 能选出至少 k 个糖果，说明甜蜜度 x 可行
        };  // 结束 check 这个 lambda
        while (l < r) {  // 二分答案：在可行区间内寻找最大的可行甜蜜度
            int mid = (l + r + 1) >> 1;  // 取上取整的中点，配合下面的 l = mid 避免死循环
            if (check(mid)) {  // mid 可行，说明答案至少是 mid
                l = mid;  // 把左边界抬到 mid
            } else {  // mid 不可行
                r = mid - 1;  // 答案严格小于 mid，右边界左移
            }  // 结束 if/else
        }  // 结束时 l == r，即最大可行甜蜜度
        return l;  // 返回最大甜蜜度
    }  // 结束 maximumTastiness
};  // 结束 Solution 类