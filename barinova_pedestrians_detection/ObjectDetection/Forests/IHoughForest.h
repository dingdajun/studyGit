#pragma once
#include "IHoughTree.h"
#include "../ImageWrapper/MultiImage.h"

#include <cstddef>

template <typename Vote>
class IHoughForest
{
public:

    std::vector < IHoughTree<Vote> *>  forest;
    std::size_t nTrees;


    MultiImage *m_testImage;
    int m_iTestImageWidth;
    int m_iTestImageHeight;

    virtual void SetNumberOfTrees(std::size_t in_iNumberOfTrees) = 0;
    virtual void setTestImage(MultiImage *im) = 0;

    // *****************************************************************************************************
    IHoughForest()
    {
        // nothing to do here
        return;
    }

    // *****************************************************************************************************
    ~IHoughForest()
    {
        for (std::size_t i = 0; i < nTrees; i ++)
        {
            delete forest[i];
        }
        return;
    }

    // *****************************************************************************************************
    bool getForestFromFile(const char *in_cForestPath, int in_iCellPatchSize)
    {
        if (in_cForestPath != NULL)
        {
            printf("Reading forest from file ...\n");

            FILE *in = fopen(in_cForestPath, "rb");

            if (!in)
            {
                std::cerr << "Forest file doesn't exist!" << std::endl;
                exit(0);
            }

            fread(&nTrees, sizeof(int), 1, in);
            SetNumberOfTrees(nTrees);

            for(int i = 0; i < nTrees; i++)
            {
                forest[i]->ReadFromFile(in);
            }
            fclose(in);

            setPatchHeight(in_iCellPatchSize);
            setPatchWidth(in_iCellPatchSize);

            printf("Done ...\n");

            return true;
        }
        else
        {
            nTrees = 0;
            forest.clear();
            return false;
        }

    }

    // *****************************************************************************************************
    void printForestToFile(const char *outpath)
    {
        FILE *out = fopen(outpath, "wb");
        fwrite(&nTrees, sizeof(int), 1, out);

        for(int i = 0; i < nTrees; i++)
        {
            forest[i]->WriteToFile(out);
        }
        fclose(out);
        return;
    }

    // *****************************************************************************************************
    void setPatchWidth(int in_PatchWidth)
    {
        for (int i = 0; i < nTrees; i ++)
        {
            forest[i]->patchWidth = in_PatchWidth;
        }
        return;
    }

    // *****************************************************************************************************
    void setPatchHeight(int in_PatchHeight)
    {
        for (int i = 0; i < nTrees; i ++)
        {
            forest[i]->patchHeight = in_PatchHeight;
        }
        return;
    }

    // *****************************************************************************************************
    int getPatchWidth()
    {
        return forest[0]->patchWidth;
    }

    // *****************************************************************************************************
    int getPatchHeight()
    {
        return forest[0]->patchHeight;
    }

};
