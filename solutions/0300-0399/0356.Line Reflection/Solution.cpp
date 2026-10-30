// 题目：356. 直线镜像（Line Reflection）
// 思路：先求所有点 x 的最小值与最大值，对称轴只能是 x = (minX + maxX) / 2；再用点集检查每个点的镜像点是否都存在。
// 时间复杂度：O(n log n)，建集合与查询都是对数代价；空间复杂度：O(n)，存放去重后的点。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool isReflected(vector<vector<int>>& points) {  // points 为点集，判断是否存在一条竖直直线使点集关于它镜像对称
        const int inf = 1 << 30;  // 取一个足够大的数作为最值的初始值
        int minX = inf, maxX = -inf;  // 记录点集中最小的 x 与最大的 x
        set<pair<int, int>> pointSet;  // 有序集合既去重又支持对数时间的成员查询
        for (auto& p : points) {  // 第一遍：求 x 的最值并建立点集
            minX = min(minX, p[0]);  // 更新最小 x
            maxX = max(maxX, p[0]);  // 更新最大 x
            pointSet.insert({p[0], p[1]});  // 记录点 (x, y)，重复点自动去重
        }  // 第一遍遍历结束
        int s = minX + maxX;  // 对称轴只能是 x = s / 2；镜像点满足 x + x' = s
        for (auto& p : points) {  // 第二遍：逐点检查镜像点是否存在
            if (!pointSet.count({s - p[0], p[1]})) {  // 镜像点 (s - x, 同一 y) 不在集合中，说明不对称
                return false;  // 只要有一个点缺镜像就返回假
            }  // 检查结束
        }  // 第二遍遍历结束
        return true;  // 所有点的镜像都在集合中，说明关于该直线对称
    }  // 方法结束
};  // 类定义结束