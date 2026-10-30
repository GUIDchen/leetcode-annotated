// 题目：3265. 统计近似相等数对 I（Count Almost Equal Pairs I）
// 思路：排序后按从小到大枚举 x，先枚举交换 x 的任意两位得到它能变成的所有去重数值，再累加哈希表中这些数此前已出现的次数。
// 时间复杂度：O(n·L³)，n 为数组长度、L 为数字位数（每个数的交换枚举为 O(L²) 次、每次转整数 O(L)）；空间复杂度：O(n + L²)，用于哈希表与去重集合。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countPairs(vector<int>& nums) {  // nums：输入数组；返回近似相等数对的数目
        sort(nums.begin(), nums.end());  // 先排序，保证每一对近似相等的数只被其中较小的那个统计到
        int ans = 0;  // ans：累计的近似相等数对数目
        unordered_map<int, int> cnt;  // cnt：已经遍历过的数的出现次数

        for (int x : nums) {  // 按非递减顺序依次处理每个数 x
            unordered_set<int> vis = {x};  // vis：x 自身以及交换两位后能得到的所有数，用于去重
            string s = to_string(x);  // 转成字符串，方便按下标交换任意两位

            for (int j = 0; j < s.length(); ++j) {  // 枚举交换的右下标 j
                for (int i = 0; i < j; ++i) {  // 枚举交换的左下标 i，只取 i<j 以避免同一对下标被处理两次
                    swap(s[i], s[j]);  // 交换第 i、j 位，构造出一个新的数
                    vis.insert(stoi(s));  // 转回整数并加入去重集合
                    swap(s[i], s[j]);  // 把字符串还原，保证枚举其他下标对时状态正确
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
