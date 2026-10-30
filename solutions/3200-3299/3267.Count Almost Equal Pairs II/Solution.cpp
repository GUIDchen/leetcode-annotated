// 题目：3267. 统计近似相等数对 II（Count Almost Equal Pairs II）
// 思路：在 I 的基础上把「至多交换两次」也枚举进来：先交换 (i, j)，再在剩余位上交换 (p, q)，把所有可达数值去重后按从小到大用哈希表累计匹配数。
// 时间复杂度：O(n·L⁴)，n 为数组长度、L 为数字位数（每个数枚举两对下标共 O(L⁴) 次，每次转整数 O(L)）；空间复杂度：O(n + L⁴)，用于哈希表与去重集合。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countPairs(vector<int>& nums) {  // nums：输入数组；返回近似相等数对的数目
        sort(nums.begin(), nums.end());  // 先排序，保证每一对近似相等的数只被其中较小的那个统计到
        int ans = 0;  // ans：累计的近似相等数对数目
        unordered_map<int, int> cnt;  // cnt：已经遍历过的数的出现次数

        for (int x : nums) {  // 按非递减顺序依次处理每个数 x
            unordered_set<int> vis = {x};  // vis：x 自身以及至多交换两次后能得到的所有数，用于去重
            string s = to_string(x);  // 转成字符串，方便按下标交换任意两位

            for (int j = 0; j < s.length(); ++j) {  // 枚举第一次交换的右下标 j
                for (int i = 0; i < j; ++i) {  // 枚举第一次交换的左下标 i，只取 i<j
                    swap(s[i], s[j]);  // 第一次交换第 i、j 位
                    vis.insert(stoi(s));  // 只交换一次的方案也要计入
                    for (int q = i + 1; q < s.length(); ++q) {  // 枚举第二次交换的右下标 q，必须避开已参与第一次交换的位置
                        for (int p = i + 1; p < q; ++p) {  // 枚举第二次交换的左下标 p，取 i<p<q 以避免重复枚举
                            swap(s[p], s[q]);  // 执行第二次交换
                            vis.insert(stoi(s));  // 至多交换两次得到的新数去重收集
                            swap(s[p], s[q]);  // 还原第二次交换
                        }
                    }
                    swap(s[i], s[j]);  // 还原第一次交换，保证枚举其他下标对时状态正确
                }
            }

            for (int y : vis) {  // 枚举 x 能变成的所有数 y
                ans += cnt[y];  // 此前出现过的每个 y 都能与 x 配成一对
            }
            cnt[x]++;  // 把 x 计入哈希表，供后面的数匹配
        }

        return ans;  // 返回数对总数
    }
};
