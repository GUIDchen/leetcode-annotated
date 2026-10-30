// 题目：2363. 合并相似的物品（Merge Similar Items）
// 思路：价值范围只有 1000，用固定长度计数数组把两个数组的权重合并累加，再按下标升序收集非零项。
// 时间复杂度：O(n + m + 1010)，近似线性；空间复杂度：O(1010)，是常数级额外空间。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<int>> mergeSimilarItems(vector<vector<int>>& items1, vector<vector<int>>& items2) {  // 入参是两组「价值, 权重」二元组，返回合并后的升序二维数组
        int cnt[1010]{};  // 计数数组：下标是价值，元素是权重和，{} 保证全部初始化为 0
        for (auto& x : items1) {  // 遍历第一个物品数组，auto& 引用避免拷贝
            cnt[x[0]] += x[1];  // 把权重累加到对应价值的下标上
        }
        for (auto& x : items2) {  // 遍历第二个物品数组
            cnt[x[0]] += x[1];  // 同一价值的权重继续累加，完成合并
        }
        vector<vector<int>> ans;  // 结果数组，按下标升序收集
        for (int i = 0; i < 1010; ++i) {  // 价值范围 1..1000，多开几个位置避免越界
            if (cnt[i]) {  // 该价值有物品才需要输出
                ans.push_back({i, cnt[i]});  // 追加一行「价值, 合并后的权重」
            }
        }
        return ans;  // 返回结果，天然按价值升序
    }
};