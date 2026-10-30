// 题目：3930. 插入后第 K 大更新的幂 II（Power Update After K-th Largest Insertion II）
// 思路：用 pb_ds 的 order statistics 树维护有序多重集，元素存成 (值, 唯一编号) 以免重复值被合并；每次插入后取第 size-k 小即第 k 大，再用快速幂把 p 更新为 p^x mod 1e9+7。
// 时间复杂度：O((n + q) log(n + q) + q log p)；空间复杂度：O(n + q)。
#include <ext/pb_ds/assoc_container.hpp>  // 引入 pb_ds 容器头文件
#include <ext/pb_ds/tree_policy.hpp>  // 引入平衡树策略与 order statistics 支持
#include <vector>  // 使用 vector

using namespace std;  // 使用标准命名空间
using namespace __gnu_pbds;  // 使用 pb_ds 命名空间

template <typename T>  // 定义一份可重复元素的有序集合别名
using ordered_multiset = tree<pair<T, int>, null_type, less<pair<T, int>>,  // 元素存成 (值, 唯一编号)，编号保证重复值也不会被合并
    rb_tree_tag, tree_order_statistics_node_update>;  // 红黑树 + 支持按排名查找的结点更新器

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> powerUpdate(vector<int>& nums, int p, vector<vector<int>>& queries) {  // nums：初始数组；p：初始底数；queries：每项是 [val, k]
        vector<int> ans;  // 存放每次查询后的 p
        ordered_multiset<int> sl;  // 维护当前所有元素的有序多重集
        const int mod = 1e9 + 7;  // 取模常数 10^9+7

        for (int i = 0; i < nums.size(); i++) {  // 把初始元素全部插入有序多重集
            sl.insert({nums[i], i});  // 下标充当唯一编号，避免重复值被合并
        }  // 初始化插入结束

        int next_id = nums.size();  // 后续插入使用的编号起点

        auto mod_pow = [&](long long base, long long exp) -> long long {  // 快速幂：计算 base^exp % mod
            long long result = 1;  // 结果初始为 1
            base %= mod;  // 底数先取模
            while (exp > 0) {  // 按二进制位从低到高处理指数
                if (exp & 1) result = (result * base) % mod;  // 当前位为 1 就把 base 乘进结果
                base = (base * base) % mod;  // 底数平方，对应下一位的权重
                exp >>= 1;  // 指数右移一位
            }  // 快速幂循环结束
            return result;  // 返回 base^exp % mod
        };  // 快速幂 lambda 结束

        for (const auto& query : queries) {  // 逐个处理查询
            int val = query[0];  // 待插入的值
            int k = query[1];  // 要求的第 k 大

            sl.insert({val, next_id++});  // 插入新值，编号自增以保证唯一

            auto it = sl.find_by_order(sl.size() - k);  // 第 k 大等于第 (size-k) 小（下标从 0 开始）
            int kth_largest = it->first;  // 取出该元素的值

            p = mod_pow(p, kth_largest);  // 把 p 更新为 p^x % mod
            ans.push_back(p);  // 记录本次查询后的 p
        }  // 查询处理结束

        return ans;  // 返回所有答案
    }  // 方法结束
};  // 类定义结束
