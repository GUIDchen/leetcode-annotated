// 题目：2838. 英雄可以获得的最大金币数（Maximum Coins Heroes Can Collect）
// 思路：怪物按能力值升序排序后求金币前缀和，每个英雄二分找出自己打得过的怪物数量，前缀和即为可独吞的金币数。
// 时间复杂度：O((n + m) log m)，排序与每个英雄的一次二分；空间复杂度：O(n + m)，下标数组、前缀和与答案数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<long long> maximumCoins(vector<int>& heroes, vector<int>& monsters, vector<int>& coins) {  // heroes 是英雄能力值；monsters 与 coins 是怪物能力值与对应金币
        int m = monsters.size();  // 怪物数量，也是金币数量
        vector<int> idx(m);  // idx 保存按怪物能力值升序排列后的原始下标
        iota(idx.begin(), idx.end(), 0);  // 先填入 0..m-1 的原始下标
        sort(idx.begin(), idx.end(), [&](int i, int j) {  // 按对应怪物的能力值升序排序
            return monsters[i] < monsters[j];  // 能力值更小的怪物排在前面
        });
        long long s[m + 1];  // 金币前缀和数组，s[i] 表示前 i 只弱怪物的金币总和
        s[0] = 0;  // 前缀和第 0 项为 0
        for (int i = 1; i <= m; ++i) {  // 依次累加排序后的金币
            s[i] = s[i - 1] + coins[idx[i - 1]];  // 前 i 只怪物的金币和
        }
        vector<long long> ans;  // 存放每个英雄能获得的金币数
        auto search = [&](int x) {  // 二分查找能力值不超过 x 的怪物数量
            int l = 0, r = m;  // 在左闭右开区间 [l, r) 上二分
            while (l < r) {  // 区间非空时继续
                int mid = (l + r) >> 1;  // 取区间中点
                if (monsters[idx[mid]] > x) {  // 中点怪物能力值大于英雄，打不过
                    r = mid;  // 把右边界收缩到 mid
                } else {  // 中点怪物能力值不超过英雄，打得过
                    l = mid + 1;  // 左边界右移，继续找更靠右的分界
                }
            }
            return l;  // 循环结束时 l 就是打得过的怪物数量
        };
        for (int h : heroes) {  // 枚举每个英雄
            ans.push_back(s[search(h)]);  // 该英雄可独吞前若干个怪物的全部金币
        }
        return ans;  // 返回所有英雄的答案
    }
};