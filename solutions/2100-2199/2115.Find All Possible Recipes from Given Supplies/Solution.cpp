// 题目：2115. 从给定原材料中找到所有可以做出的菜（Find All Possible Recipes from Given Supplies）
// 思路：把「原料 → 依赖它的菜」建成有向图，菜的入度为所需原料数；以初始原料为起点做拓扑排序（BFS），入度归零的菜即可做出。
// 时间复杂度：O(N + E)，N 为原料/菜总数、E 为依赖边数；空间复杂度：O(N + E)，存图与入度表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<string> findAllRecipes(vector<string>& recipes, vector<vector<string>>& ingredients, vector<string>& supplies) {  // recipes：菜名；ingredients：每道菜所需原料；supplies：初始原料；返回所有能做出的菜
        unordered_map<string, vector<string>> g;  // 邻接表：原料 -> 依赖它的菜，是依赖图的反向边
        unordered_map<string, int> indeg;  // 每道菜的入度 = 还缺少的原料种数
        for (int i = 0; i < recipes.size(); ++i) {  // 遍历每道菜，建立依赖关系
            for (auto& v : ingredients[i]) {  // 遍历该菜所需的每一种原料
                g[v].push_back(recipes[i]);  // 原料 v 能解锁菜 recipes[i]，连一条边 v -> 菜
            }  // 单道菜的原料处理完毕
            indeg[recipes[i]] = ingredients[i].size();  // 初始入度设为所需原料总数
        }  // 建图结束
        queue<string> q;  // BFS 队列，存放已经可以拿到的「材料」（初始原料或已做出的菜）
        for (auto& s : supplies) {  // 初始原料天然可得
            q.push(s);  // 全部入队作为起点
        }  // 起点准备完毕
        vector<string> ans;  // 记录最终能做出的菜，按拓扑顺序加入
        while (!q.empty()) {  // 队列非空说明还有材料可以向外扩散
            for (int n = q.size(); n; --n) {  // 按层遍历：只处理本轮开始时就已在队列中的材料
                auto i = q.front();  // 取队首材料
                q.pop();  // 出队
                for (auto j : g[i]) {  // 遍历所有依赖材料 i 的菜
                    if (--indeg[j] == 0) {  // 少了一种缺失原料；入度归零说明这道菜的原料已凑齐
                        ans.push_back(j);  // 记入答案
                        q.push(j);  // 这道菜本身又可作为别的菜的材料，入队继续扩散
                    }  // 入度还不为零则继续等待
                }  // 当前材料的所有出边处理完毕
            }  // 本层遍历结束
        }  // 拓扑过程结束
        return ans;  // 返回所有能做出的菜
    }  // findAllRecipes 方法结束
};  // Solution 类定义结束