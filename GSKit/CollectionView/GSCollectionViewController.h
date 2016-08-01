//
//  GSCollectionViewController.h
//  GSKitDemo
//
//  Created by OSU on 16/7/28.
//  Copyright © 2016年 GarryLance. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "GSCollectionViewModel.h"
#import "GSCollectionViewSectionModel.h"
#import "GSCollectionViewItemModel.h"
#import "GSCollectionViewItem.h"



@protocol GSCollectionViewControllerDelegate;



@interface GSCollectionViewController : UICollectionViewController

@property (assign, nonatomic) id <GSCollectionViewControllerDelegate> gs_delegate;

/**section的模型数组*/
@property (copy, nonatomic, readonly) NSArray <GSCollectionViewSectionModel *> * gs_sectionModels;

/**item的字典，keyArray与sectionModels一一对应，排序由sectionModels决定*/
@property (copy, nonatomic, readonly) NSDictionary <GSCollectionViewSectionModel *, NSArray <GSCollectionViewItemModel *> *> * gs_itemsSectionDict;

/**选中item回调*/
@property (assign, nonatomic) void(^gs_didSelectCollectionViewItemBlock)(GSCollectionViewController * vc, __kindof GSCollectionViewItem * item, __kindof GSCollectionViewItemModel * itemModel);


/**
 生成常用的UICollectionViewFlowLayout
 @param itemSize        单元大小
 @param lineSpacing     单元滑动方向的最小间距
 @param itemSpacing     单元排序顺序方向的最小间距
 @param sectionInset    每组上左下右空位
 @param scrollDirection 滑动方向
 */
- (instancetype)initWithCommonLayoutWithItemSize:(CGSize)itemSize
                                     lineSpacing:(CGFloat)lineSpacing
                                     itemSpacing:(CGFloat)itemSpacing
                                    sectionInset:(UIEdgeInsets)sectionInset
                                 scrollDirection:(UICollectionViewScrollDirection)scrollDirection;


/**
 设置item类型、重用标记、section和item的model类型
 @param itemClass         item对应的类型，应为GSCollectionViewItem的子类
 @param sectionModelClass section对应的模型类型，应为GSCollectionViewSectionModel的子类
 @param itemModelClass    item对应的模型类型，应为GSCollectionViewItemModel的子类
 */
- (void)registerItemClass:(Class)itemClass
          reuseIdentifier:(NSString *)reuseIdentifier
        sectionModelClass:(Class)sectionModelClass
           itemModelClass:(Class)itemModelClass;


/**
 安装数据模型
 @param sectionCount      设置section数量。
 @param itemsCountBlock   一个回调，返回对应section的item数量（根据sectionCount决定调用多少次）。
 @param sectionModelBlock 一个回调，根据section对sectionModel进行业务操作（根据sectionCount决定调用多少次）。
 @param itemModelBlock    一个回调，根据indexPath对itemModel进行业务操作(有多少个item调用多少次，即itemsCountBlock返回值总数)。
 */
- (void)numberOfSections:(NSInteger)sectionCount
           numberOfItems:(NSInteger(^)(NSInteger section))itemsCountBlock
        modelsForSection:(void(^)(__kindof GSCollectionViewSectionModel * sectionModel, NSInteger section))sectionModelBlock
           modelsForItem:(void(^)(__kindof GSCollectionViewItemModel * itemModel, NSIndexPath * indexPath))itemModelBlock;


/**
 安装item事件回调
 @param sectionModel   item对应的sectionModel
 @param willSetupBlock 一个item即将开始安装的回调
 @param didSetupBlock  一个item完成安装的回调
 */
- (void)blockFotItemSection:(GSCollectionViewSectionModel *)sectionModel
         itemWillSetupBlock:(GSItemWillSetupDataBlock)willSetupBlock
          itemDidSetupBlock:(GSItemDidSetupDataBlock)didSetupBlock;



@end



@protocol GSCollectionViewControllerDelegate <NSObject>

@optional

@end
