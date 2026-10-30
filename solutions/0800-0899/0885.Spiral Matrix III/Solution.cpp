// 题目：885. 螺旋矩阵 III（Spiral Matrix III）
// 思路：从起点开始按「右、下、左、上」走，每圈步长依次为 1、1、2、2、3、3……，只把落在矩阵内的坐标加入答案。
// 时间复杂度：O(rows × cols)，每个格子只记录一次（另有少量界外行走）；空间复杂度：O(rows × cols)，保存答案。
class Solution {  // LeetCode 约定的题解类
public:  // 方法对外可见
    vector<vector<int>> spiralMatrixIII(int rows, int cols, int rStart, int cStart) {  // rows/cols：矩阵行数与列数；rStart/cStart：起点坐标
        int cnt = rows * cols;  // 需要收集的格子总数
        vector<vector<int>> ans;  // 按螺旋顺序记录坐标
        ans.push_back({rStart, cStart});  // 起点先放入答案
        if (cnt == 1) return ans;  // 只有一个格子时直接返回
        for (int k = 1;; k += 2) {  // 每圈起始步长为 1，之后每次加 2；循环无上界，收集满即返回
            vector<vector<int>> dirs = {{0, 1, k}, {1, 0, k}, {0, -1, k + 1}, {-1, 0, k + 1}};  // 右、下、左、上四段的步数序列（后两段多走一步）
            for (auto& dir : dirs) {  // 依次走四个方向
                int r = dir[0], c = dir[1], dk = dir[2];  // 行增量、列增量、本段要走的步数
                while (dk-- > 0) {  // 沿当前方向走 dk 步
                    rStart += r;  // 行坐标前进
                    cStart += c;  // 列坐标前进
                    if (rStart >= 0 && rStart < rows && cStart >= 0 && cStart < cols) {  // 只有落在矩阵内的格子才记录
                        ans.push_back({rStart, cStart});  // 合法格子加入答案
                        if (ans.size() == cnt) return ans;  // 收集满就立即返回
                    }
                }
            }
        }
    }  // 方法结束
};  // 类定义结束