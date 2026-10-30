// 题目：755. 倒水（Pour Water）——中等（付费题）
// 思路：一滴一滴模拟。每滴水先尽量向左流、再尽量向右流，落到路径上最低且最靠边的格子；两边都流不动就落在 k 处。
// 时间复杂度：O(volume * n)，每滴水最多把整个数组扫描一遍；空间复杂度：O(1)，直接在原数组上累加高度。
class Solution {  // LeetCode 约定的题解类
public:  // 接口对外可见
    vector<int> pourWater(vector<int>& heights, int volume, int k) {  // heights 是地形高度，volume 是水量，k 是倒水位置
        while (volume--) {  // 逐滴处理：每轮倒一滴水
            bool find = false;  // 标记这滴水是否已经找到落点
            for (int d = -1; d < 2 && !find; d += 2) {  // d=-1 先向左找，d=1 再向右找；一旦找到就停止
                int i = k, j = k;  // i 是扫描位置，j 记录路径上最低的位置（初始认为原地最低）
                while (i + d >= 0 && i + d < heights.size() && heights[i + d] <= heights[i]) {  // 只要下一格不比当前格高，水就能继续流
                    if (heights[i + d] < heights[i]) {  // 遇到严格更低的格子
                        j = i + d;  // 更新最低落点（取最靠外的那个更低位置）
                    }
                    i += d;  // 朝该方向前进一格
                }
                if (j != k) {  // 找到了比 k 处更低的落点
                    find = true;  // 这滴水已经安排好，不再尝试另一侧
                    ++heights[j];  // 在最低处把高度加一，等价于落下一滴水
                }
            }
            if (!find) {  // 左右两个方向都流不动
                ++heights[k];  // 只能堆在倒水位置 k 上
            }
        }
        return heights;  // 返回最终地形
    }
};