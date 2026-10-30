// 题目：1184. 公交站间的距离（Distance Between Bus Stops）
// 思路：环形线路上只有两个方向，先算出总长，再沿顺时针从 start 走到 destination 得到一段距离 t，
//       答案就是 min(t, 总长 - t)。时间复杂度 O(n)，空间复杂度 O(1)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int distanceBetweenBusStops(vector<int>& distance, int start, int destination) {  // distance[i] 为第 i 站到下一站的距离，start/destination 为起终点站号
        int s = accumulate(distance.begin(), distance.end(), 0);  // 整条环形线路的总长度
        int t = 0, n = distance.size();  // t 累计顺时针距离，n 为站数（取模保证下标成环）
        while (start != destination) {  // 沿顺时针一站站前进，直到抵达终点
            t += distance[start];  // 累加当前站到下一站的距离
            start = (start + 1) % n;  // 下标前进一格，对 n 取模实现环形回绕
        }  // 顺时针这一侧的距离已经算完
        return min(t, s - t);  // 另一方向长度为总长减去顺时针距离，取较小者即答案
    }  // 方法体结束
};  // 题解类结束
