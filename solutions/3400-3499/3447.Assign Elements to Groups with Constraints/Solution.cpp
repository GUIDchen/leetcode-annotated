// 题目：3447. 将元素分配给有约束条件的组（Assign Elements to Groups with Constraints）
// 思路：每个组只关心 groups[i] 的最早可用约数是谁，所以反过来从元素出发：用 d[v] 记录「v 被哪个下标的元素整除」的最小下标，按元素下标从小到大枚举，把 x 的所有不超过最大组值的倍数 y 中尚未填过的 d[y] 填成当前下标。因为是从小到大枚举，先填进去的一定是最小下标（优先级最高），之后不再覆盖。
// 时间复杂度：O(mx log mx)，mx 为最大组值，枚举倍数是调和级数；空间复杂度：O(mx)，需要一个长度 mx+1 的表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> assignElements(vector<int>& groups, vector<int>& elements) {  // groups：各组的目标值；elements：可用元素；返回每组的分配下标
        int mx = ranges::max(groups);  // mx 是 groups 里的最大值，只需处理到 mx 为止
        vector<int> d(mx + 1, -1);  // d[v] 记录能整除 v 的最小元素下标，-1 表示还没有元素能整除 v

        for (int j = 0; j < elements.size(); ++j) {  // 按 elements 的下标顺序（优先级从高到低）依次处理
            int x = elements[j];  // x 是当前元素的值
            if (x > mx || d[x] != -1) {  // x 超出上限则整除不了任何组值；d[x] 已有值说明更靠前的元素已经覆盖了 x
                continue;  // 跳过这个元素
            }
            for (int y = x; y <= mx; y += x) {  // 枚举 x 的所有不超过 mx 的倍数 y
                if (d[y] == -1) {  // 只填第一次出现的那个（下标最小，优先级最高）
                    d[y] = j;  // 记下 y 对应的是第 j 个元素
                }
            }
        }

        vector<int> ans(groups.size());  // 答案数组，长度与 groups 一致
        for (int i = 0; i < groups.size(); ++i) {  // 逐个组查表得到分配的元素下标
            ans[i] = d[groups[i]];  // 直接取该组数的最小约数下标，-1 表示无法分配
        }

        return ans;  // 返回每组分配到的元素下标
    }  // 方法结束
};  // 类定义结束
