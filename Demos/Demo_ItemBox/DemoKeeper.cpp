/*!
	@file
	@author		Albert Semenov
	@date		05/2008
	@module
*/
#include "precompiled.h"
#include "DemoKeeper.h"
#include "CellView.h"
#include "Base/Main.h"

namespace demo
{

	void DemoKeeper::notifyStartDrop(wraps::BaseLayout * _sender, wraps::DDItemInfo _info, bool & _result)
	{
		if (_info.sender_index != MyGUI::ITEM_NONE)
		{
			ItemData * data = *((ItemBox*)_info.sender)->getItemDataAt<ItemData*>(_info.sender_index);
			_result = !data->isEmpty();
		}
	}

	void DemoKeeper::notifyRequestDrop(wraps::BaseLayout * _sender, wraps::DDItemInfo _info, bool & _result)
	{
		// �� �� ����� ������
		if (_info.receiver_index == MyGUI::ITEM_NONE)
		{
			_result = false;
			return;
		}

		// �� ���� � �� ����� �����
		if ((_info.sender == _info.receiver) && (_info.sender_index == _info.receiver_index))
		{
			_result = false;
			return;
		}

		ItemData * sender_data = *((ItemBox*)_info.sender)->getItemDataAt<ItemData*>(_info.sender_index);
		ItemData * receiver_data = *((ItemBox*)_info.receiver)->getItemDataAt<ItemData*>(_info.receiver_index);

		_result = receiver_data->isEmpty() || receiver_data->compare(sender_data);
	}

	void DemoKeeper::notifyEndDrop(wraps::BaseLayout * _sender, wraps::DDItemInfo _info, bool _result)
	{
		if (_result)
		{

			ItemData * sender_data = *((ItemBox*)_info.sender)->getItemDataAt<ItemData*>(_info.sender_index);
			ItemData * receiver_data = *((ItemBox*)_info.receiver)->getItemDataAt<ItemData*>(_info.receiver_index);

			receiver_data->add(sender_data);
			sender_data->clear();


			((ItemBox*)_info.receiver)->setItemData(_info.receiver_index, receiver_data);
			((ItemBox*)_info.sender)->setItemData(_info.sender_index, sender_data);
		}

	}

	void DemoKeeper::notifyNotifyItem(wraps::BaseLayout * _sender, const MyGUI::IBNotifyItemData & _info)
	{
		/*if (_info.index != MyGUI::ITEM_NONE)
		{
			if (_info.notify == MyGUI::NotifyItem::NOTIFY_MOUSE_RELEASED)
			{
				MyGUI::ItemBoxPtr sender = ((BaseItemBox<CellView>*)_sender)->getItemBox();
				//sender->
				sender->setPosition(sender->getCoord());
			}
		}*/
	}

	void DemoKeeper::notifyDropState(wraps::BaseLayout * _sender, MyGUI::DDItemState _state)
	{
		/*if (_state == MyGUI::DDItemState::Refuse) MyGUI::PointerManager::getInstance().setPointer("drop_refuse", _sender->mainWidget());
		else if (_state == MyGUI::DDItemState::Accept) MyGUI::PointerManager::getInstance().setPointer("drop_accept", _sender->mainWidget());
		else if (_state == MyGUI::DDItemState::Miss) MyGUI::PointerManager::getInstance().setPointer("drop", _sender->mainWidget());
		else if (_state == MyGUI::DDItemState::Start) MyGUI::PointerManager::getInstance().setPointer("drop", _sender->mainWidget());
		else if (_state == MyGUI::DDItemState::End) MyGUI::PointerManager::getInstance().setDefaultPointer();*/
	}

	void DemoKeeper::setupResources()
	{
		base::BaseManager::setupResources();
		addResourceLocation(mRootMedia + "/Demos/Demo_ItemBox");
		addResourceLocation(mRootMedia + "/Icons");
		addResourceLocation(mRootMedia + "/Common/Wallpapers");
	}

	void DemoKeeper::createScene()
	{
		// ������������ ��� ������ �������
		MyGUI::FactoryManager::getInstance().registryFactory<ResourceItemInfo>("Resource");

		setWallpaper("wallpaper0.jpg");
		setDescriptionText("You can drag and drop items from one ItemBox to another. Hold mouse over item to see tool tip. Resize windows to see vertical and horizontal ItebBox alignments.");
		MyGUI::Gui::getInstance().load("Resources.xml");
		MyGUI::Gui::getInstance().load("ItemBox_skin.xml");

		mToolTip = new ToolTip();
		mToolTip->hide();

		mItemBoxV = new ItemBoxWindow("ItemBoxV.layout");
		mItemBoxV->getItemBox()->addItem(new ItemData());
		mItemBoxV->getItemBox()->addItem(new ItemData("info_Crystal_Clear_Item1", 5));
		mItemBoxV->getItemBox()->addItem(new ItemData("info_Crystal_Clear_Item2", 5));
		mItemBoxV->getItemBox()->addItem(new ItemData("info_Crystal_Clear_Item3", 5));
		mItemBoxV->getItemBox()->addItem(new ItemData("info_Crystal_Clear_Item4", 5));
		mItemBoxV->getItemBox()->addItem(new ItemData("info_Crystal_Clear_Item5", 5));
		mItemBoxV->getItemBox()->addItem(new ItemData("info_Crystal_Clear_Item6", 5));
		mItemBoxV->getItemBox()->addItem(new ItemData("info_Crystal_Clear_Item7", 5));
		mItemBoxV->getItemBox()->addItem(new ItemData("info_Crystal_Clear_Item8", 5));
		mItemBoxV->getItemBox()->addItem(new ItemData("info_Crystal_Clear_Item9", 5));

		mItemBoxV->getItemBox()->eventStartDrag = MyGUI::newDelegate(this, &DemoKeeper::notifyStartDrop);
		mItemBoxV->getItemBox()->eventRequestDrop = MyGUI::newDelegate(this, &DemoKeeper::notifyRequestDrop);
		mItemBoxV->getItemBox()->eventDropResult = MyGUI::newDelegate(this, &DemoKeeper::notifyEndDrop);
		mItemBoxV->getItemBox()->eventChangeDDState = newDelegate(this, &DemoKeeper::notifyDropState);
		mItemBoxV->getItemBox()->eventNotifyItem = newDelegate(this, &DemoKeeper::notifyNotifyItem);
		mItemBoxV->getItemBox()->eventToolTip = newDelegate(this, &DemoKeeper::notifyToolTip);

		mItemBoxH = new ItemBoxWindow("ItemBoxH.layout");
		mItemBoxH->getItemBox()->addItem(new ItemData());
		mItemBoxH->getItemBox()->addItem(new ItemData("info_Crystal_Clear_Item1", 5));
		mItemBoxH->getItemBox()->addItem(new ItemData("info_Crystal_Clear_Item2", 5));
		mItemBoxH->getItemBox()->addItem(new ItemData("info_Crystal_Clear_Item3", 5));
		mItemBoxH->getItemBox()->addItem(new ItemData("info_Crystal_Clear_Item4", 5));
		mItemBoxH->getItemBox()->addItem(new ItemData("info_Crystal_Clear_Item5", 5));
		mItemBoxH->getItemBox()->addItem(new ItemData("info_Crystal_Clear_Item6", 5));
		mItemBoxH->getItemBox()->addItem(new ItemData("info_Crystal_Clear_Item7", 5));
		mItemBoxH->getItemBox()->addItem(new ItemData("info_Crystal_Clear_Item8", 5));
		mItemBoxH->getItemBox()->addItem(new ItemData("info_Crystal_Clear_Item9", 5));

		mItemBoxH->getItemBox()->eventStartDrag = MyGUI::newDelegate(this, &DemoKeeper::notifyStartDrop);
		mItemBoxH->getItemBox()->eventRequestDrop = MyGUI::newDelegate(this, &DemoKeeper::notifyRequestDrop);
		mItemBoxH->getItemBox()->eventDropResult = MyGUI::newDelegate(this, &DemoKeeper::notifyEndDrop);
		mItemBoxH->getItemBox()->eventChangeDDState = newDelegate(this, &DemoKeeper::notifyDropState);
		mItemBoxH->getItemBox()->eventNotifyItem = newDelegate(this, &DemoKeeper::notifyNotifyItem);
		mItemBoxH->getItemBox()->eventToolTip = newDelegate(this, &DemoKeeper::notifyToolTip);


	}

	void DemoKeeper::destroyScene()
	{
		// ��� ������ �������
		MyGUI::FactoryManager::getInstance().unregistryFactory<ResourceItemInfo>("Resource");

		delete mItemBoxH;
		mItemBoxH = 0;

		delete mItemBoxV;
		mItemBoxV = 0;

		delete mToolTip;
		mToolTip = 0;
	}

	void DemoKeeper::notifyToolTip(wraps::BaseLayout * _sender, const MyGUI::ToolTipInfo & _info, ItemData * _data)
	{
		if (_info.type == MyGUI::ToolTipInfo::Show)
		{
			mToolTip->show(_data, _info.point);
		}
		else if (_info.type == MyGUI::ToolTipInfo::Hide)
		{
			mToolTip->hide();
		}
	}

} // namespace demo

MYGUI_APP(demo::DemoKeeper)
