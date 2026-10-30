// 题目：1224. 最大相等频率（Maximum Equal Frequency）
// 思路：边扫边维护 cnt（每个数的出现次数）与 ccnt（频率 → 拥有该频率的数字个数），只需判断三种「删掉一个元素后频率全相等」的形态：所有数频率为 1、最大频率只多出一次、存在一个孤立的一次数。
// 时间复杂度：O(n)，哈希表均摊 O(1)；空间复杂度：O(n)，两个哈希表的元素个数。
class Solution {  // LeetCode 约定的题解类
public:  // 方法对外可见
    int maxEqualFreq(vector<int>& nums) {  // nums：输入数组；返回删除一个元素后能让所有数频率相等的最大前缀长度
        unordered_map<int, int> cnt;  // cnt[v]：值 v 到目前为止出现的次数
        unordered_map<int, int> ccnt;  // ccnt[c]：出现次数恰好为 c 的不同值有几个（频率的频率）
        int ans = 0, mx = 0;  // ans：当前最大合法前缀长度；mx：已出现过的最大频率
        for (int i = 1; i <= nums.size(); ++i) {  // i 是前缀长度（从 1 开始，nums[i-1] 是刚加入的数）
            int v = nums[i - 1];  // 取出本前缀新加入的这个数
            if (cnt[v]) --ccnt[cnt[v]];  // 它原来属于频率 cnt[v] 这一组，先把这一组的计数减 1
            ++cnt[v];  // 该数的出现次数加 1
            mx = max(mx, cnt[v]);  // 维护最大频率；频率只增不减，所以直接取 max
            ++ccnt[cnt[v]];  // 新频率这一组的计数加 1
            if (mx == 1)  // 情况一：最大频率为 1，说明每个数都只出现一次
                ans = i;  // 再删掉任意一个数后剩下仍全部相等，整个前缀合法
            else if (ccnt[mx] * mx + ccnt[mx - 1] * (mx - 1) == i && ccnt[mx] == 1)  // 情况二：最大频率那组只有一个数且比别的数多 1 次，删掉它多出的那一次即可
                ans = i;  // 「最大频率组 + 次大频率组」正好拼成前缀长度，说明当前可以相等
            else if (ccnt[mx] * mx + 1 == i && ccnt[1] == 1)  // 情况三：存在一个只出现 1 次的孤立数，其余数频率相同
                ans = i;  // 删掉这个孤立数后总数正好减 1，当前前缀也合法
        }  // 结束对前缀长度的枚举
        return ans;  // 返回最大合法前缀长度
    }  // 方法结束
};  // 类定义结束