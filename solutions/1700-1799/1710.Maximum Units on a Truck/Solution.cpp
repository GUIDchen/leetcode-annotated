// 题目：1710. 卡车上的最大单元数（Maximum Units on a Truck）
// 思路：贪心，按每箱单元数从大到小排序，依次尽量装满收益最高的规格，直到卡车装不下为止。
// 时间复杂度：O(n log n)，主要是排序；空间复杂度：O(1)，排序原地进行，不计返回值。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maximumUnits(vector<vector<int>>& boxTypes, int truckSize) {  // boxTypes 每项为 [箱子数, 每箱单元数]；truckSize 是可装的箱数上限
        sort(boxTypes.begin(), boxTypes.end(), [](auto& a, auto& b) { return a[1] > b[1]; });  // 按每箱单元数从大到小排序，优先装收益高的规格
        int ans = 0;  // 累计能装上的单元总数
        for (auto& e : boxTypes) {  // 依次考虑每种规格的箱子
            int a = e[0], b = e[1];  // a 是该规格的箱子数，b 是每箱的单元数
            ans += b * min(truckSize, a);  // 该规格最多再装 min(剩余容量, 该规格箱数) 箱，再乘每箱单元数累加
            truckSize -= a;  // 扣除该规格的全部箱数（若超出会变负，下一行立即退出）
            if (truckSize <= 0) break;  // 卡车已经装满，无需再考虑收益更低的规格
        }  // 本规格处理结束
        return ans;  // 返回最大单元总数
    }  // 方法结束
};  // 类定义结束