#include "../common/common_wx.h"
#include <wx/listctrl.h>
#include <vector>

static std::vector<long> GetCurrentSelectItems(wxListCtrl * mainListCtrl) {
	long itemIndex = -1;
	std::vector<long> selectedItems;
	//auto &fileModel = RemoteFileModel::Instance();
	//auto list = fileModel.GetCurrentList();
	//long count = list.size();
	long currentIdx = 0;
	while ((itemIndex = mainListCtrl->GetNextItem(itemIndex,
		wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED)) != wxNOT_FOUND) {
		// Got the selected item index
		//wxLogDebug(listControl->GetItemText(itemIndex));
		// got
		//auto list = fileModel.GetCurrentList();

		//if (itemIndex >= count) {
		//	break;
		//}
		//auto& fileData = list.at(static_cast<web::json::array::size_type>(itemIndex));
		//if (fileData.is_null()) {
		//	break;
		//}

		if (itemIndex > -1) {
			selectedItems.push_back(itemIndex);
		}
		currentIdx++;
		if (currentIdx > 99999) {
			break;
		}
	}
	return selectedItems;
}