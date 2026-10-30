// 题目：1743. 从相邻元素对还原数组（Restore the Array From Adjacent Pairs）
// 思路：把相邻对看成无向图的边建邻接表，度数为 1 的节点一定是数组端点；从端点出发沿邻接表依次排除已用元素往后推。
// 时间复杂度：O(n)，建图与还原各遍历一遍；空间复杂度：O(n)，邻接表存放 2(n-1) 条边。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> restoreArray(vector<vector<int>>& adjacentPairs) {  // adjacentPairs：打乱顺序的相邻元素对
        int n = adjacentPairs.size() + 1;  // 相邻对数量比元素个数少 1，所以原数组长度是 size+1
        unordered_map<int, vector<int>> g;  // 邻接表：每个元素值映射到与它相邻的所有元素
        for (auto& e : adjacentPairs) {  // 遍历每个相邻对，把这条无向边双向写入邻接表
            int a = e[0], b = e[1];  // 取出这一对相邻元素
            g[a].push_back(b);  // a 的邻居里加上 b
            g[b].push_back(a);  // b 的邻居里加上 a
        }
        vector<int> ans(n);  // 用来按顺序还原出原数组
        for (auto& [k, v] : g) {  // 遍历邻接表，找只出现一个邻居的端点（结构体绑定拆出键 k 和邻居表 v）
            if (v.size() == 1) {  // 度数为 1 说明它是原数组的端点
                ans[0] = k;  // 端点放在还原数组的第一个位置
                ans[1] = v[0];  // 端点唯一的邻居就是第二个元素
                break;  // 起点已确定，无需继续找
            }
        }
        for (int i = 2; i < n; ++i) {  // 从第三个位置开始，沿着链一路往后推
            auto v = g[ans[i - 1]];  // 取出前一个元素在邻接表里的邻居列表（长度为 1 或 2）
            ans[i] = v[0] == ans[i - 2] ? v[1] : v[0];  // 排除掉已经用过的那个邻居，剩下的就是下一个元素
        }
        return ans;  // 返回还原出的原数组
    }
};