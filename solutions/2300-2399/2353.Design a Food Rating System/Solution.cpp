// 题目：2353. 设计食物评分系统（Design a Food Rating System）
// 思路：每个菜系维护有序集合 {(-评分, 菜名)}，评分取负使 begin() 就是最高分、同分时菜名字典序最小；再用菜名 → (评分, 菜系) 反查表，改分时先删旧键再插新键。
// 时间复杂度：构造 O(n log n)，changeRating / highestRated 各 O(log n)；空间复杂度：O(n)。
class FoodRatings {  // 设计类：需支持构造、改分、查询最高分三种操作
public:  // 三个接口对外可见
    FoodRatings(vector<string>& foods, vector<string>& cuisines, vector<int>& ratings) {  // 构造函数：foods / cuisines / ratings 为三组等长数组，第 i 项描述同一道菜
        for (int i = 0; i < foods.size(); ++i) {  // 逐道菜建立索引
            string food = foods[i], cuisine = cuisines[i];  // 取出第 i 道菜的菜名与所属菜系
            int rating = ratings[i];  // 取出第 i 道菜的初始评分
            d[cuisine].insert({-rating, food});  // 按菜系分桶：评分取负放入 set，越负越靠前，同分时菜名字典序小的靠前
            g[food] = {rating, cuisine};  // 反查表：菜名 → (当前评分, 菜系)，改分时靠它还原出旧记录
        }  // 全部菜品登记完毕，结束循环
    }  // 构造函数结束

    void changeRating(string food, int newRating) {  // 修改某道菜的评分，题目保证菜名一定存在
        auto [oldRating, cuisine] = g[food];  // 结构化绑定取出旧评分与菜系：删除旧键必须还原出原来的 (评分, 菜名)
        g[food] = {newRating, cuisine};  // 先更新反查表，让它与有序集合里的新键保持一致
        d[cuisine].erase({-oldRating, food});  // 从该菜系的有序集合里删掉「旧评分」那一项
        d[cuisine].insert({-newRating, food});  // 再按「新评分」插回，集合始终按 (-评分, 菜名) 有序
    }  // changeRating 结束

    string highestRated(string cuisine) {  // 查询该菜系中评分最高、同分时名称字典序最小的菜名
        return d[cuisine].begin()->second;  // begin() 是排序后的第一项，其 second 就是菜名
    }  // highestRated 结束

private:  // 以下为内部数据结构，不对外暴露
    unordered_map<string, set<pair<int, string>>> d;  // 菜系 → 有序集合 {(-评分, 菜名)}：按评分降序排好，同分再按菜名升序
    unordered_map<string, pair<int, string>> g;  // 菜名 → (评分, 菜系)：O(1) 反查，供 changeRating 定位并删除旧键
};  // 类定义结束

// 以下是 LeetCode 判题器自动生成的使用示例，属于注释内容，原样保留
/**
 * Your FoodRatings object will be instantiated and called as such:
 * FoodRatings* obj = new FoodRatings(foods, cuisines, ratings);
 * obj->changeRating(food,newRating);
 * string param_2 = obj->highestRated(cuisine);
 */
