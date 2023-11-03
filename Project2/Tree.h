#pragma once

#include "framework.h"
#include "Direct2D.h"

// 父類別 Images
// 不使用Images //因有多種fruit
//class Images {
//protected:
//    ID2D1Bitmap* treeBitmap;  //繪圖圖片 
//    ID2D1Bitmap* fruitBitmap; //繪圖圖片
//    //std::vector<ID2D1Bitmap*> fruitBitmaps;
//public:
//
//    Images() { 
//        treeBitmap = NULL;
//        fruitBitmap = NULL; 
//    };
//    void Release_Bitmap()
//    {
//        if (treeBitmap) {
//            treeBitmap->Release();
//            //重新賦值
//            treeBitmap = NULL;
//        }
//        if (fruitBitmap) {
//            fruitBitmap->Release();
//            //重新賦值
//            fruitBitmap = NULL;
//        }
//
//        std::wstring message =  L"釋放Bitmap\n";
//        OutputDebugString(message.c_str());
//    }
//    void Release_treeBitmap()
//    {
//        if (treeBitmap) {
//            treeBitmap->Release();
//            //重新賦值
//            treeBitmap = NULL;
//        }
//    }
//    void Release_fruitBitmap()
//    {
//        if (fruitBitmap) {
//            fruitBitmap->Release();
//            //重新賦值
//            fruitBitmap = NULL;
//        }
//    }
//    ID2D1Bitmap*& Get_treeBitmap() { return treeBitmap; }
//    ID2D1Bitmap*& Get_fruitBitmap() { return fruitBitmap; }
//
//};

// 子類別 Tree
class Tree /*: public Images*/ {
protected:
    ID2D1Bitmap* treeBitmap;  //繪圖圖片 
    //drawPoint tree_Point;
public:
    Tree() { return; }
    Tree(HWND hwnd,ID2D1HwndRenderTarget* mRenderTarget,
        std::wstring path ) {
        IWICImagingFactory* pIWICFactory = NULL;
        CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, (LPVOID*)&pIWICFactory);
        int errorcode = 0;
        Common::LoadBitmapFromFile(mRenderTarget, pIWICFactory, path, 0, 0, &treeBitmap, hwnd, errorcode);
        if (errorcode != 0) {
            std::wstring str1 = path + L"圖檔不存在" + L"\n";
            OutputDebugString(path.c_str());
        }
        //tree_Point = point;
        pIWICFactory->Release();
    }

    void Release_treeBitmap()
    {
        if (treeBitmap) {
            treeBitmap->Release();
            //重新賦值
            treeBitmap = NULL;
        }
    }
    ID2D1Bitmap*& Get_treeBitmap() { return treeBitmap; }

    //繪畫樹木
    void drawTree(ID2D1HwndRenderTarget* mRenderTarget, drawPoint point, int treeSize) {
        if (treeBitmap) {
            mRenderTarget->DrawBitmap(treeBitmap, D2D1::RectF(point.x, point.y, point.x + treeSize, point.y + treeSize));
        }
    }
    //void Set_tree_Point(drawPoint Point) {
    //    tree_Point = Point;
    //}
    //drawPoint Get_tree_Point() {
    //    return tree_Point;
    //};

};

class Fruit /*: public Images  */ {
protected:
    ID2D1Bitmap* fruitBitmap; //繪圖圖片
    std::vector<drawPoint> fruit_Points;
public:
    Fruit() { return; }
    Fruit(HWND hwnd, ID2D1HwndRenderTarget* mRenderTarget,
        std::wstring path, std::vector<drawPoint> points) {
        IWICImagingFactory* pIWICFactory = NULL;
        CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, (LPVOID*)&pIWICFactory);
        int errorcode = 0;
        Common::LoadBitmapFromFile(mRenderTarget, pIWICFactory, path, 0, 0, &fruitBitmap, hwnd, errorcode);
        if (errorcode != 0) {
            std::wstring str1 = path + L"圖檔不存在" + L"\n";
            OutputDebugString(path.c_str());
        }
        fruit_Points = points;
        pIWICFactory->Release();
    }
    void Release_fruitBitmap()
    {
        if (fruitBitmap) {
            fruitBitmap->Release();
            //重新賦值
            fruitBitmap = NULL;
        }
    }
    ID2D1Bitmap*& Get_fruitBitmap() { return fruitBitmap; }

    //繪畫水果
    void drawFruit(ID2D1HwndRenderTarget* mRenderTarget, drawPoint treepoint,int pxSize , int OriginalSize) {
        if (fruitBitmap) {
            //計算水果在樹上縮放的大小
            double scalingRatio = static_cast<double>(pxSize) / OriginalSize;
            int scalingPx = DIALOG_TREELOAD_FRUIT_PX * scalingRatio;

            for (auto& coordinate : fruit_Points) {
                UINT drawpoint_x = treepoint.x + coordinate.x * scalingRatio;
                UINT drawpoint_y = treepoint.y + coordinate.y * scalingRatio;
                    mRenderTarget->DrawBitmap(fruitBitmap, D2D1::RectF(drawpoint_x, drawpoint_y, drawpoint_x + scalingPx, drawpoint_y + scalingPx));
            }
        }
    }
    void Set_fruit_Points(std::vector<drawPoint> points) {
        fruit_Points = points;
    }
    std::vector<drawPoint> Get_fruit_Points() {
        return fruit_Points;
    };
};


// 子類別 FruitTree
class FruitTree : public Tree {
private:
    std::vector<Fruit*> Fruits;
    //drawPoint point; //point目前是給Manager管理 
public:
    FruitTree() { return; }
    FruitTree(HWND hwnd, ID2D1HwndRenderTarget* mRenderTarget,
        std::wstring treepath) : Tree(hwnd, mRenderTarget, treepath) {
        // 在構造函數的成員初始化列表中呼叫基類的構造函數並傳遞正確的參數
        ;
        // 可以進一步初始化 Fruits，如果有必要
    }
    ~FruitTree() {
        // 釋放 Fruits 中的資源
        for (auto& fruit : Fruits) {
            delete fruit;
        }
    }

    void AddFruit(HWND hwnd, ID2D1HwndRenderTarget* mRenderTarget,
        std::wstring path, std::vector<drawPoint> points) {
        Fruit* newfruit = new Fruit(hwnd, mRenderTarget, path, points) ;
        Fruits.push_back(newfruit);
    }

    void drawFruitTree(ID2D1HwndRenderTarget* mRenderTarget,drawPoint treepoint, int treeSize , int OriginalSize) {
        drawTree(mRenderTarget, treepoint,  treeSize);
        for (auto& fruit : Fruits) {
            OutputDebugString(L"drawFruitTree\n");
            fruit->drawFruit(mRenderTarget, treepoint, treeSize, OriginalSize);
        }
    }
    void Release_Bitmap()
    {
        if (Get_treeBitmap()) {
            treeBitmap->Release();
            //重新賦值
            treeBitmap = NULL;
        }

        for (auto& fruit : Fruits) {
            if (fruit->Get_fruitBitmap()) 
                fruit->Release_fruitBitmap();
        }
        std::wstring message = L"釋放Bitmap\n";
        OutputDebugString(message.c_str());
    }
};

// 子類別 FruitTrees
// 目前架構 
// 一個Tree 包含 一張樹木圖片 
// 一個Fruit 包含一個水果圖片 以及n個水果座標
// 一個FruitTree 繼承一個Tree 包含N個Fruit
// 一個FruitTreeManager 包含一個FruitTree 以及n個樹木座標 以及繪圖相關函數

class FruitTreeManager {
private:
    HWND hwnd;
    ID2D1HwndRenderTarget* RenderTarget;

    int pxSize;  //轉換大小
    int OriginalSize; //水果與樹木原圖大小 目前基本是200
    FruitTree* m_FruitTree;
    std::vector<drawPoint> m_points;

public:
    FruitTreeManager(HWND mhwnd, ID2D1HwndRenderTarget* mRenderTarget) {
        hwnd = mhwnd;
        RenderTarget = mRenderTarget;
    }
    void Add_points(drawPoint point) {
        auto it = std::lower_bound(m_points.begin(), m_points.end(), point);
        m_points.insert(it, point);
    }
    void Erase_points(drawPoint erasePoint, int fixedPx) {

        // 講點擊位置移動回圖片左上方
        int xPos = erasePoint.x + fixedPx / 2;
        int yPos = erasePoint.y + fixedPx;

        //auto it = std::find_if(m_points.begin(), m_points.end(),
        //    [xPos, yPos, fixedPx](const drawPoint& point) {
        //        return point.x <= xPos && point.x >= xPos - fixedPx &&
        //            point.y <= yPos && point.y >= yPos - fixedPx;
        //    });

        //if (it != m_points.end()) {
        //    m_points.erase(it);
        //}
        std::vector<drawPoint> matchingPoints;
        std::copy_if(m_points.begin(), m_points.end(), std::back_inserter(matchingPoints),
            [xPos, yPos, fixedPx](const drawPoint& point) {
                auto isWithinRange = [xPos, yPos, fixedPx](const drawPoint& p) {
                    return p.x <= xPos && p.x >= xPos - fixedPx &&
                        p.y <= yPos && p.y >= yPos - fixedPx;
                };
                return isWithinRange(point);
            });
        // 按照排序條件排序
        std::sort(matchingPoints.begin(), matchingPoints.end(),
            [](const drawPoint& point1, const drawPoint& point2) {
                if (point1.y == point2.y) {
                    return point1.x < point2.x;
                }
                return point1.y < point2.y;
            });

        //// 刪除最大的元素
        if (!matchingPoints.empty()) {
            auto it_remove = std::remove(m_points.begin(), m_points.end(), matchingPoints.back());
            m_points.erase(it_remove, m_points.end());
        }
    }
    void SetFruitTree(std::wstring treepath , json Fruit_Data , std::filesystem::path currentPath) {
        if (m_FruitTree)
            delete m_FruitTree;
        m_FruitTree = new FruitTree(hwnd, RenderTarget, treepath);
        if (!Fruit_Data.is_null())
        {
            OutputDebugString(L"\n");
            OutputDebugString(L"Fruit_Data\n");

            for (auto Fruit : Fruit_Data.items()) {
                std::string FruitName = Fruit.key();
                std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
                std::wstring fruitpath;
                std::vector<drawPoint> points;

                if (Fruit_Data.contains(FruitName)) {
                    // 路徑
                    std::wstring image = converter.from_bytes(Fruit_Data[FruitName]["image"]);
                    fruitpath = currentPath.parent_path().wstring() + L"\\種樹\\Images\\" + image;
                    OutputDebugString(fruitpath.c_str());
                    OutputDebugString(L"\n");

                    // 座標
                    for (const auto coordinate : Fruit_Data[FruitName]["coordinates"]) {
                        drawPoint Fruit_Point;
                        Fruit_Point.x = coordinate["X"];
                        Fruit_Point.y = coordinate["Y"];
                        points.push_back(Fruit_Point);
                    }
                }
                m_FruitTree->AddFruit(hwnd, RenderTarget, fruitpath, points);

            }

        }
    }
    std::vector<drawPoint> GetPoints() { return m_points; }
    void ClearPoints() { m_points.clear(); }
    json PointsToJson() {
        json coordinatesArray;
        // 將 points 中的每個 drawPoint 轉換為 JSON object 並添加到 array 中
        for (const drawPoint& point : m_points)
        {
            json pointObject =
            {
                {"X", point.x},
                {"Y", point.y}
            };

            coordinatesArray.push_back(pointObject);
        }
        return coordinatesArray;
    }


    bool is_TreeExist() {
        if (!m_FruitTree || !m_FruitTree->Get_treeBitmap())
            return 0;
        else
            return 1;
    }
    //treeSize 為樹木在地圖上出現的大小 fruitSize 為水果在元件盤上出現的大小
    void draw(int treeSize, int OriginalSize) {
        for (auto point : m_points) {
            m_FruitTree->drawFruitTree(RenderTarget, point , treeSize ,  OriginalSize);
        }
    }
};