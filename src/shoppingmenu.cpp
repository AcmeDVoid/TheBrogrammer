#include "include/shoppingmenu.h"
#include "ui_shoppingmenu.h"

/**
 * @brief shoppingMenu::shoppingMenu
 * ---------------------------------------------------------------------------------------
 * Pass in a std::queue of integers that represents the indexes of the restaurants that
 * you want to show in this shopping menu.
 *
 * Also pass in a pointer to the master restaurant list that manages all the restaurants
 * hint: this is typically the restaurant list that you load at the initilization of the
 * program, and the same list that the admin menu classes modifies.
 *
 * Based on the indexes in the queue passed in, we will then build a NEW restaurant list
 * for use in this shopping menu. It will only contain restaurants based on the indexes
 * that were in the queue.
 * ---------------------------------------------------------------------------------------
 * @param sortedRestaurantIndexes a std::queue of integers representing indexes from the
 * original masterList that you want to show in the shopping menu.
 * @param masterList a pointer to the master restaurant list that the program uses.
 * @param parent - a qt thing, the parent object defaults to 0
 */
shoppingMenu::shoppingMenu(stack<string> pathStack,
                           StadiumList* masterList, QStringList selectedStadiums,
                           QWidget *parent)
    : QDialog(parent), ui(new Ui::shoppingMenu) {

    originalSelections = selectedStadiums;
    string stadiumName;    //storage for the index form the restaurant list
    idxCounter = 0;
    totalDistance = 0;

    //store a reference to the master list in the object
    masterStadiumList = masterList;

    //allocate space for the new reference list
    StadiumList* listOfSelectedStadiums = new StadiumList();

    //iterate through the queue
    while(!pathStack.empty()){
        //get the first index in the stack and pop remove it
        stadiumName = pathStack.top();
        pathStack.pop();

        //call the copy constructor, the restaurant(idx) method returns pointer,
        //we dereference the restaurant at the index popped from the queue and
        //store it into this newRestaurant object
        Stadium newStadium = *(masterStadiumList->stadium(stadiumName));

        //then add that new restaurant into the reference list
        listOfSelectedStadiums->addStadium( newStadium );
    }

    //ui inits
    ui->setupUi(this);

    //set cart headers and column sizes
    QStringList cartHeaders;
    cartHeaders.push_back("Item");
    cartHeaders.push_back("Price");
    cartHeaders.push_back("Quantity");
    cartHeaders.push_back("Sub-Total");
    ui->cart->setColumnCount(cartHeaders.count());
    ui->cart->setHeaderLabels(cartHeaders);
    ui->cart->expandAll();
    ui->cart->setContextMenuPolicy(Qt::CustomContextMenu);

    //save the reference list to the object
    selectedRestaurants = listOfSelectedStadiums;

    //allocated choices vector
    choices = new purchaseChoices;

    //start the travesal through the restaurant list and save each
    //item selected in the ui
    startSelectingItems(idxCounter);
}

/**
 * @brief shoppingMenu::~shoppingMenu
 * shoppingMenu destructor just closes the window - built by qt
 */
shoppingMenu::~shoppingMenu()
{
    delete ui;
}


/**
 * @brief shoppingMenu::buildMenuSelectionList
 * This method puts menu items and prices into the right-most column of the ui (menuitemsList)
 * based on the index you passed into it, the menuItemsList listView widget will be populated
 * with the restaurant's menu items at the index you passed in.
 * @param selectedIndex the index of the restaurant you want to build menu items for.
 */
void shoppingMenu::buildMenuSelectionList(int selectedIndex){
    //save a reference to the restaurant the user selected
    Stadium* stadium = selectedRestaurants->stadium(selectedIndex);
    int menuSize = stadium->souvenirList()->size();

    //set row and column count
    ui->menu->setColumnCount(3);
    ui->menu->setRowCount(menuSize);

    //set table headers
    ui->menu->setHorizontalHeaderItem(0,new QTableWidgetItem("Item"));
    ui->menu->setHorizontalHeaderItem(1,new QTableWidgetItem("Price"));
    ui->menu->setHorizontalHeaderItem(2,new QTableWidgetItem("Quantity"));

    for( int i = 0; i < menuSize; i++){
        //get name and price from vector
        QString name = QString::fromStdString(stadium->souvenirList()->at(i).name());
        double price = stadium->souvenirList()->at(i).price();
        int quantity = 0;

        //name
        //syntax: row, column, item
        ui->menu->setItem(i,0,new QTableWidgetItem(name));

        //price
        ui->menu->setItem(i, 1, new QTableWidgetItem(QString::number(price)) );

        //quantity
        QSpinBox* qty = new QSpinBox();
        //connect(priceEdit, SIGNAL(valueChanged(double)), this, SLOT(detectChange(double)));
        qty->setValue(quantity);
        ui->menu->setCellWidget(i, 2, qty);
    }
}

/** addToCart
 * @brief shoppingMenu::addToCart this method adds an item to the cart
 * @param currentIndex the index of the restaurant to add an item to
 */
void shoppingMenu::addToCart(int currentIndex){
    bool itemAdded = false;

    //get menu size and restaurant pointer
    int menuSize = selectedRestaurants->stadium(currentIndex)->souvenirList()->size();
    Stadium* stadium = selectedRestaurants->stadium(currentIndex);

    //add a root-level item to the cart
    QTreeWidgetItem* root = new QTreeWidgetItem(ui->cart);
    root->setText(0,QString::fromStdString(stadium->name()));

    for(int i = 0; i < menuSize; i++){
        //build a purchase
        purchase* thisPurchase = new purchase;

        //NOTE:
        //0 -> item name
        //1 -> item price
        //2 -> spinBox ptr

        //get spinBox ptr
        QSpinBox* spinBox = qobject_cast<QSpinBox*>(ui->menu->cellWidget(i,2));

        //get name, price, and quantity from the menu table
        QString itemName = ui->menu->item(i, 0)->text();
        double price     = ui->menu->item(i, 1)->text().toDouble();
        int quantity     = spinBox->value();
        double total     = price*quantity;

        if(quantity > 0){
            itemAdded = true;
            thisPurchase->itemName = itemName;
            thisPurchase->price    = price;
            thisPurchase->quantity = quantity;

            choices->purchases.push_back(thisPurchase);

            QTreeWidgetItem* child = new QTreeWidgetItem(root);
            child->setText(0,itemName);
            child->setText(1,QString::number(price));
            child->setText(2,QString::number(quantity));
            child->setText(3,QString::number(total));
        }
    }
    if(itemAdded == true){
        ui->cart->addTopLevelItem(root);
    }
    else{
        delete root;
    }
    ui->cart->expandAll();
}


bool shoppingMenu::isInOriginalSelectionsList( int i ){
    QString stadiumName = QString::fromStdString(selectedRestaurants->stadium(i)->name());
    int idx = originalSelections.indexOf(stadiumName);
    return idx > -1;

}

/**
 * @brief shoppingMenu::startSelectingItems
 * start selecting menu items by traversing through the listOfSelectedRestaurants
 * @param i the index of the restaurant to start selecting items of
 */
void shoppingMenu::startSelectingItems(int i){


    if(i == 0){
        //on the 1st stadium we visit the distance is 0 miles, b/c we are starting here
        totalDistance += 0;
    }
    else{
        totalDistance += masterStadiumList->graph()->length
        (
            masterStadiumList->graph()->findVertex(selectedRestaurants->stadium(i)->name()) ,
            masterStadiumList->graph()->findVertex(selectedRestaurants->stadium(i - 1)->name())
        );
    }
    ui->distance->setText("Distance Traveled: " + QString::number(totalDistance));

    //add the restaurant name to the visited history list
    ui->visitHistory->addItem(QString::fromStdString(selectedRestaurants->stadium(i)->name()));
    this->visitHistory.push_back(QString::fromStdString(selectedRestaurants->stadium(i)->name()));


    //If last restaurant in trip, hide the next button and label to signify the trip is over
    //when okay is pressed.
    if( i == this->selectedRestaurants->size() - 1){
        ui->next->hide();
        ui->status->setText("Click Okay to Finish Trip.");
    }


    //we check to see if the stadium we are currently visiting was part of the original stadiums that the user
    //wanted to visit ( by using the check-marks on the trip-planner window)
    //if the stadium IS in this list then we want to allow the user to buy items from it.
    if( isInOriginalSelectionsList(i)){
        //ui->restaurantLogo->setPixmap(QPixmap(QString::fromStdString(selectedRestaurants->restaurant(i)->getLogoPath())));
        ui->teamName->setText(QString::fromStdString(selectedRestaurants->stadium(i)->team()));
        ui->restaurantName->setText(QString::fromStdString(selectedRestaurants->stadium(i)->name()) );

        ui->menu->clear();
        buildMenuSelectionList(i);
    }
    //otherwise, we essentially just click 'next' for the user without giving them the option to buy
    //anything at this staidum
    else{
        on_next_clicked();
    }


}

//*********************************************
//this code is not used - DEPRECATED
QPixmap shoppingMenu::selectLogo(int idx){
    QString imgPath = ":/logos/";

    switch(idx){
    case 0: imgPath += "mcdonalds_logo.png";
        break;
    case 1: imgPath += "chipotle_logo.png";
        break;
    case 2: imgPath += "dominos_logo.png";
        break;
    case 3: imgPath += "kfc_logo.png";
        break;
    case 4: imgPath += "subway_logo.png";
        break;
    case 5: imgPath += "innout_logo.png";
        break;
    case 6: imgPath += "wendys_logo.png";
        break;
    case 7: imgPath += "jackinthebox_logo.png";
        break;
    case 8: imgPath += "elpolloloco_logo.png";
        break;
    case 9: imgPath += "papajohns_logo.png";
        break;
    case 10: imgPath += "pizzahut_logo.png";
        break;
    case 11: imgPath += "sonic_logo.png";
        break;
    default: imgPath += "default.png";
    }

    return QPixmap(imgPath);
}

/** SLOT
 * @brief shoppingMenu::on_next_clicked
 */
void shoppingMenu::on_next_clicked()
{
    if(idxCounter + 1 < selectedRestaurants->size()){
        startSelectingItems(++idxCounter);
    }
}

/** SLOT
 * @brief shoppingMenu::on_prev_clicked
 * NOTE: unimplemented
 */
void shoppingMenu::on_prev_clicked()
{
    if(idxCounter != 0){
        startSelectingItems(--idxCounter);
    }
}

/** SLOT
 * @brief shoppingMenu::on_addToCart_clicked
 * add a menu item to the cart
 */
void shoppingMenu::on_addToCart_clicked()
{
    addToCart(idxCounter);

    //loop over the menu and get each spinBox Ptr and set its value back to 0
    int menuSize = selectedRestaurants->stadium(idxCounter)->souvenirList()->size();
    for(int i = 0; i < menuSize; i++){
        //get spinBox ptr
        QSpinBox* spinBox = qobject_cast<QSpinBox*>(ui->menu->cellWidget(i,2));
        spinBox->setValue(0);
    }
}

/**
 * @brief shoppingMenu::modifyCartItem
 * Allows right-click context menu support for modifying items in
 * the cart
 * @param p QAction pointer of where the click happned on the UI
 */
void shoppingMenu::modifyCartItem(QAction* p){
    if(p->text() == "Delete Item"){
        if(ui->cart->currentItem() != NULL){
            delete ui->cart->currentItem();
        }
    }
    else{
        if(ui->cart->currentItem() != NULL && ui->cart->currentItem()->childCount() == 0){
            changeIntValue* changeIntWindow = new changeIntValue(ui->cart->currentItem());
            changeIntWindow->setWindowFlags(changeIntWindow->windowFlags() & ~Qt::WindowContextHelpButtonHint);
            changeIntWindow->exec();
        }
    }
}

/**
 * @brief shoppingMenu::on_cart_customContextMenuRequested
 * pops up a right-click context menu for modifying cart items
 * @param pos position of type QPoint of where the click occured
 */
void shoppingMenu::on_cart_customContextMenuRequested(const QPoint &pos)
{
    QMenu *menu = new QMenu(this);
    QAction* deleteItem = new QAction("Delete Item", this);
    QAction* changeQty  = new QAction("Change Quantity", this);

    menu->addAction(deleteItem);
    menu->addSeparator();
    menu->addAction(changeQty);
    menu->popup(ui->cart->viewport()->mapToGlobal(pos));

    connect(menu, SIGNAL(triggered(QAction*)), this, SLOT(modifyCartItem(QAction*)));
}

/**
 * @brief shoppingMenu::buildChoicesFromCart
 * Tihs method is essentially a toVector() method with this
 * programs custom data. It takes the QTreeQWidget data and
 * stores it into a vector so that we can pass this data along
 * Note: this is O(n^2)
 * @return a vector of restaurantChoices (a vector of structs)
 */
vector<purchaseChoices*> shoppingMenu::buildChoicesFromCart(){
    vector<purchaseChoices*> allChoices;

    for(int i = 0; i < ui->cart->topLevelItemCount(); i++){
        purchaseChoices* menuChoices = new purchaseChoices;

        //save a reference to root widget item
        QTreeWidgetItem* topItem = ui->cart->topLevelItem(i);

        QString restaurantName = topItem->text(0);  //restaurant name
        menuChoices->restaurantName = restaurantName;

        for(int j = 0; j < topItem->childCount(); j++){
            //save a reference to the child element
            QTreeWidgetItem* child = topItem->child(j);

            QString menuItem = child->text(0);             //menu item name
            double  price    = child->text(1).toDouble();  //price
            int     quantity = child->text(2).toInt();     //quantity

            //add purchase data to a struct
            purchase* userPurchase = new purchase();
            userPurchase->itemName = menuItem;
            userPurchase->price    = price;
            userPurchase->quantity = quantity;

            //add the struct to the choices vector
            menuChoices->purchases.push_back(userPurchase);

        } //end inner-for

        allChoices.push_back(menuChoices);
    }//end outter-for
    return allChoices;
}

/** SLOT
 * @brief shoppingMenu::on_okay_cancel_acceptedt
 * This method adds advances the user to the next window
 */
void shoppingMenu::on_okay_cancel_accepted()
{
    shoppingSummaryWindow* summaryWindow = new shoppingSummaryWindow(buildChoicesFromCart(), masterStadiumList, totalDistance, visitHistory);
    summaryWindow->setWindowFlags(summaryWindow->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    summaryWindow->exec();
}
