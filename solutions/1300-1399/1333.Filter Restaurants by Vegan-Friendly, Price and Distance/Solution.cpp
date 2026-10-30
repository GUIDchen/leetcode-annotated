// 题目：1333. 餐厅过滤器（Filter Restaurants by Vegan-Friendly, Price and Distance）
// 思路：先按「评分降序、评分相同则 id 降序」整体排序，再线性扫描一遍，把同时满足素食、价格、距离三项条件的 id 收进答案，顺序天然符合要求。
// 时间复杂度：O(n log n)，排序是瓶颈，扫描是 O(n)；空间复杂度：O(n)，答案数组最多存 n 个 id（排序只用常数级额外空间）。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> filterRestaurants(vector<vector<int>>& restaurants, int veganFriendly, int maxPrice, int maxDistance) {  // restaurants 每条记录为 [id, rating, veganFriendly, price, distance]；三个参数是过滤条件
        sort(restaurants.begin(), restaurants.end(), [](const vector<int>& a, const vector<int>& b) {  // 先整体排序：评分高的在前，评分相同则 id 大的在前，这样后面只需按顺序收集
            if (a[1] != b[1]) {  // 两条记录评分不同时，以评分为主序
                return a[1] > b[1];  // 评分降序
            }  // 评分相同，此时才看 id
            return a[0] > b[0];  // id 也按降序排
        });  // 排序结束
        vector<int> ans;  // 存放筛选后餐厅的 id
        for (auto& r : restaurants) {  // 按已排好的顺序遍历每家餐厅
            if (r[2] >= veganFriendly && r[3] <= maxPrice && r[4] <= maxDistance) {  // 三项条件都要满足：素食友好度达标、价格不超上限、距离不超上限
                ans.push_back(r[0]);  // 条件全部满足，记录该餐厅 id
            }  // 条件分支结束
        }  // 遍历结束
        return ans;  // 返回按「评分降序、id 降序」排好序的 id 列表
    }  // 方法结束
};  // 类定义结束