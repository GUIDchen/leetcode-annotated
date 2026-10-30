// 题目：1196. 最多可以买到的苹果数量（How Many Apples Can You Put into the Basket）
// 思路：重量升序排序后从最轻的开始装，累加重量，一旦超过 5000 就返回已经装好的个数。
// 时间复杂度：O(n log n)，排序主导；空间复杂度：O(1)，原地排序只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxNumberOfApples(vector<int>& weight) {  // weight 是每个苹果的重量，返回最多能装进容量 5000 的篮子的苹果个数
        sort(weight.begin(), weight.end());  // 升序排序：贪心地先装最轻的，才能装下最多数量
        int s = 0;  // s 累计已装苹果的总重量
        for (int i = 0; i < weight.size(); ++i) {  // 按下标从小到大枚举每个苹果
            s += weight[i];  // 试着把第 i 个苹果装进篮子
            if (s > 5000) {  // 总重超过篮子 5000 的容量上限
                return i;  // 这个装不下了，答案就是前面已经装好的 i 个
            }
        }
        return weight.size();  // 所有苹果都装下了，答案是苹果总数
    }
};