// 题目：1452. 收藏清单（People Whose List of Favorite Companies Is Not a Subset of Another List）
// 核心思路：先把公司名离散化成整数编号，把每个人的清单变成整数集合；再两两比较，若第 i 个人的集合是某个 j 的子集就淘汰 i。
// 时间复杂度：O(n^2 * m)，n 为人数、m 为单份清单长度；空间复杂度：O(n * m)，存放离散化后的集合。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> peopleIndexes(vector<vector<string>>& favoriteCompanies) {  // 返回那些「收藏清单不是别人收藏清单子集」的人的下标
        int n = favoriteCompanies.size();  // 人数，也就是清单份数
        unordered_map<string, int> d;  // 公司名 → 整数编号的哈希表，把长字符串压缩成整数，方便集合运算
        int idx = 0;  // 下一个可分配的公司编号
        vector<unordered_set<int>> nums(n);  // 每个人的收藏集合，元素是公司编号

        for (int i = 0; i < n; ++i) {  // 逐个处理每个人的清单
            for (const auto& s : favoriteCompanies[i]) {  // 遍历这个人收藏的每一家公司
                if (!d.contains(s)) {  // 该公司名是第一次出现，需要分配新编号
                    d[s] = idx++;  // 记录映射关系，并把编号计数器加一
                }  // if 分支结束
                nums[i].insert(d[s]);  // 把该公司对应的编号加入第 i 个人的集合
            }  // 内层循环结束
        }  // 外层循环结束

        auto check = [](const unordered_set<int>& a, const unordered_set<int>& b) {  // 判断集合 a 是否为集合 b 的子集
            for (int x : a) {  // 遍历 a 中的每个元素
                if (!b.contains(x)) {  // a 里有一个元素不在 b 里，说明 a 不是 b 的子集
                    return false;  // 立刻返回 false
                }  // if 分支结束
            }  // for 循环结束
            return true;  // a 的所有元素都在 b 中，是子集
        };  // lambda 定义结束

        vector<int> ans;  // 存放答案下标（要求升序，按 i 递增遍历天然有序）
        for (int i = 0; i < n; ++i) {  // 逐个检查第 i 个人是否应该保留
            bool ok = true;  // 先假设第 i 个人的清单不是任何人的子集
            for (int j = 0; j < n && ok; ++j) {  // 一旦发现被包含就提前结束内层循环
                if (i != j && check(nums[i], nums[j])) {  // 排除自己，检查第 i 个人的清单是否为第 j 个人的子集
                    ok = false;  // 是别人的子集，标记为不合法
                }  // if 分支结束
            }  // 内层比较循环结束
            if (ok) {  // 不是任何其他人的子集
                ans.push_back(i);  // 把该下标加入答案
            }  // if 分支结束
        }  // 外层循环结束

        return ans;  // 返回所有满足条件的下标
    }  // peopleIndexes 方法结束
};  // 类定义结束
