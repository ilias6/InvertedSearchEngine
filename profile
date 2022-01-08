Flat profile:

Each sample counts as 0.01 seconds.
  %   cumulative   self              self     total           
 time   seconds   seconds    calls  ms/call  ms/call  name    
 37.65      1.31     1.31  1071597     0.00     0.00  Word::editDist(Word&)
  8.77      1.62     0.31 80917280     0.00     0.00  int const& std::min<int>(int const&, int const&)
  6.75      1.85     0.24  1452273     0.00     0.00  Scheduler::assignJob()
  4.31      2.00     0.15  1523557     0.00     0.00  BKTree::search(BKNode*, Word*, int)
  4.31      2.15     0.15                             doJobFunction(void*)
  3.45      2.27     0.12  1934680     0.00     0.00  Scheduler::doJob(Job*, int)
  2.01      2.34     0.07  1699714     0.00     0.00  Queue<Job*>::pop()
  1.72      2.40     0.06   407866     0.00     0.00  biSearchQueryIndex(Vector<Query*>*, unsigned int)
  1.58      2.46     0.06   962629     0.00     0.00  Word::exactMatch(Word&)
  1.58      2.51     0.06   407292     0.00     0.00  Word::hammingDist(Word&)
  1.44      2.56     0.05  3665617     0.00     0.00  Job::getId()
  1.44      2.61     0.05  1732320     0.00     0.00  Index::search(Word*, int)
  1.29      2.66     0.05  4772702     0.00     0.00  Word::getLen()
  1.15      2.70     0.04 17725370     0.00     0.00  ListNode<PayloadEntry>::getNext() const
  1.15      2.74     0.04   833034     0.00     0.00  djb2(char const*)
  1.15      2.78     0.04   463496     0.00     0.00  PayloadEntry::getActive()
  1.15      2.82     0.04   456434     0.00     0.00  List<PayloadEntry>::getItem(int) const
  0.86      2.85     0.03  4539798     0.00     0.00  Query::getId()
  0.86      2.88     0.03  4170434     0.00     0.00  List<Entry*>::List()
  0.86      2.91     0.03  3476799     0.00     0.00  checkCondition(pthread_mutex_t*, pthread_mutex_t*, bool*)
  0.86      2.94     0.03  2433484     0.00     0.00  List<Entry*>::append(List<Entry*>*)
  0.86      2.97     0.03   656185     0.00     0.00  Query::getWord(int)
  0.86      3.00     0.03   419344     0.00     0.00  Result::increaseCounter(unsigned int, Word*)
  0.86      3.03     0.03   209132     0.00     0.00  CoreWrapper::searchWordInIndeces(Word*, Result*, int)
  0.86      3.06     0.03      450     0.07     0.09  Result::Result(unsigned int, Vector<Query*>&)
  0.72      3.08     0.03  5511035     0.00     0.00  List<Entry*>::~List()
  0.57      3.10     0.02  5643141     0.00     0.00  Vector<Query*>::getItem(int) const
  0.57      3.12     0.02  1992770     0.00     0.00  SearchMethodArgs::SearchMethodArgs(Result*, Word*, int, int, int)
  0.57      3.14     0.02  1630904     0.00     0.00  Job::~Job()
  0.57      3.16     0.02  1628222     0.00     0.00  ListNode<Job*>::~ListNode()
  0.57      3.18     0.02  1598464     0.00     0.00  List<Job*>::removeIdx(int)
  0.57      3.20     0.02  1383688     0.00     0.00  Vector<BKNode*>::getItem(int) const
  0.57      3.22     0.02  1329316     0.00     0.00  Vector<Entry*>::getLen() const
  0.43      3.24     0.02  1769313     0.00     0.00  SearchMethodArgs::getType()
  0.43      3.25     0.02  1755649     0.00     0.00  SearchMethodArgs::getWord()
  0.43      3.27     0.02  1457018     0.00     0.00  List<Entry*>::List(List<Entry*> const&)
  0.43      3.28     0.02  1434595     0.00     0.00  Vector<BKNode*>::getLen() const
  0.43      3.30     0.02        1    15.00    15.00  _GLOBAL__sub_I__ZN4WordC2EPKc
  0.43      3.31     0.02                             operator<<(std::ostream&, Word const&)
  0.29      3.32     0.01  4092783     0.00     0.00  List<Entry*>::getLen() const
  0.29      3.33     0.01  2406559     0.00     0.00  Entry::getWord()
  0.29      3.34     0.01  2039710     0.00     0.00  ListNode<Job*>::ListNode(Job*&)
  0.29      3.35     0.01  2020657     0.00     0.00  List<Job*>::insert(Job*&, Job***)
  0.29      3.36     0.01  1936053     0.00     0.00  Job::Job(JobId, Args*)
  0.29      3.37     0.01  1887017     0.00     0.00  Scheduler::addJob(Job*)
  0.29      3.38     0.01  1693333     0.00     0.00  SearchMethodArgs::~SearchMethodArgs()
  0.29      3.39     0.01  1667359     0.00     0.00  CoreWrapper::increaseCounter(List<Entry*>&, Result*, MatchType, unsigned int)
  0.29      3.40     0.01  1606898     0.00     0.00  List<Job*>::getItem(int) const
  0.29      3.41     0.01  1524318     0.00     0.00  BKNode::getChildren()
  0.29      3.42     0.01   438267     0.00     0.00  Bucket::bucketSize()
  0.29      3.43     0.01   398725     0.00     0.00  Vector<Query*>::getLen() const
  0.29      3.44     0.01   189998     0.00     0.00  Vector<Entry*>::insert(Entry*&)
  0.29      3.45     0.01      414     0.02     0.02  Vector<Query*>::Vector(Vector<Query*> const&)
  0.29      3.46     0.01       67     0.15     0.15  BKNode::~BKNode()
  0.14      3.47     0.01  1769907     0.00     0.00  SearchMethodArgs::getDist()
  0.14      3.47     0.01  1767450     0.00     0.00  SearchMethodArgs::getParentIndex()
  0.14      3.48     0.01        1     5.00     5.00  _GLOBAL__sub_I__ZN6BKTreeC2EM4WordFiRS0_E
  0.14      3.48     0.01                             giveJobFunction(void*)
  0.00      3.48     0.00  2388260     0.00     0.00  List<PayloadEntry>::~List()
  0.00      3.48     0.00  2267835     0.00     0.00  List<PayloadEntry>::List()
  0.00      3.48     0.00  2008926     0.00     0.00  Queue<Job*>::push(Job*&)
  0.00      3.48     0.00  1998648     0.00     0.00  ListNode<Job*>::setNext(ListNode<Job*>*)
  0.00      3.48     0.00  1906623     0.00     0.00  Args::Args()
  0.00      3.48     0.00  1767044     0.00     0.00  SearchMethodArgs::getRes()
  0.00      3.48     0.00  1722323     0.00     0.00  Job::getArgs()
  0.00      3.48     0.00  1687707     0.00     0.00  SearchMethodArgs::~SearchMethodArgs()
  0.00      3.48     0.00  1678432     0.00     0.00  Word::getStr()
  0.00      3.48     0.00  1675490     0.00     0.00  Args::~Args()
  0.00      3.48     0.00  1621665     0.00     0.00  ListNode<Job*>::getNext() const
  0.00      3.48     0.00  1579112     0.00     0.00  Queue<Job*>::getList()
  0.00      3.48     0.00  1562015     0.00     0.00  ListNode<Job*>::getData()
  0.00      3.48     0.00  1517491     0.00     0.00  BKTree::search(Word*, int)
  0.00      3.48     0.00  1484212     0.00     0.00  List<Job*>::getLen() const
  0.00      3.48     0.00  1459926     0.00     0.00  BKNode::getData()
  0.00      3.48     0.00  1397507     0.00     0.00  BKNode::getDist()
  0.00      3.48     0.00  1137392     0.00     0.00  Query::getWordsInQuery()
  0.00      3.48     0.00   629397     0.00     0.00  HashTable::getEntry(Word*)
  0.00      3.48     0.00   624946     0.00     0.00  Bucket::getEntry(Word*)
  0.00      3.48     0.00   507724     0.00     0.00  Vector<Entry*>::getItem(int) const
  0.00      3.48     0.00   471340     0.00     0.00  Vector<Entry*>::Vector()
  0.00      3.48     0.00   466087     0.00     0.00  Bucket::Bucket()
  0.00      3.48     0.00   456920     0.00     0.00  ListNode<PayloadEntry>::getData()
  0.00      3.48     0.00   454670     0.00     0.00  Vector<Entry*>::~Vector()
  0.00      3.48     0.00   450610     0.00     0.00  Bucket::~Bucket()
  0.00      3.48     0.00   429601     0.00     0.00  Word::Word(char const*)
  0.00      3.48     0.00   424787     0.00     0.00  Word::~Word()
  0.00      3.48     0.00   408065     0.00     0.00  PayloadEntry::~PayloadEntry()
  0.00      3.48     0.00   406457     0.00     0.00  PayloadEntry::getId()
  0.00      3.48     0.00   371280     0.00     0.00  satisfy(bool*, int)
  0.00      3.48     0.00   224990     0.00     0.00  Document::getWord(int)
  0.00      3.48     0.00   205482     0.00     0.00  ListNode<PayloadEntry>::~ListNode()
  0.00      3.48     0.00   200137     0.00     0.00  Bucket::getEntry(int)
  0.00      3.48     0.00   199134     0.00     0.00  ListNode<PayloadEntry>::ListNode(PayloadEntry&)
  0.00      3.48     0.00   196859     0.00     0.00  PayloadEntry::PayloadEntry(PayloadEntry&)
  0.00      3.48     0.00   194997     0.00     0.00  Entry::~Entry()
  0.00      3.48     0.00   194170     0.00     0.00  Entry::addToPayload(PayloadEntry&, MatchType, unsigned int)
  0.00      3.48     0.00   193021     0.00     0.00  PayloadEntry::PayloadEntry(unsigned int, bool*)
  0.00      3.48     0.00   192346     0.00     0.00  List<PayloadEntry>::insert(PayloadEntry&, PayloadEntry**)
  0.00      3.48     0.00   191630     0.00     0.00  Bucket::insert(Entry*)
  0.00      3.48     0.00   187476     0.00     0.00  Entry::Entry(Word&, PayloadEntry&, MatchType, unsigned int)
  0.00      3.48     0.00   186526     0.00     0.00  HashTable::insert(Entry*)
  0.00      3.48     0.00   184970     0.00     0.00  Word::Word(Word&)
  0.00      3.48     0.00    94326     0.00     0.00  ListNode<Entry*>::getNext() const
  0.00      3.48     0.00    63213     0.00     0.00  ListNode<Entry*>::~ListNode()
  0.00      3.48     0.00    61606     0.00     0.00  ListNode<Entry*>::getData()
  0.00      3.48     0.00    61514     0.00     0.00  ListNode<Entry*>::ListNode(Entry*&)
  0.00      3.48     0.00    47264     0.00     0.00  List<Entry*>::insert(Entry*&, Entry***)
  0.00      3.48     0.00    46777     0.00     0.00  List<Entry*>::getItem(int) const
  0.00      3.48     0.00    16352     0.00     0.00  Entry::getPayload(MatchType, unsigned int)
  0.00      3.48     0.00    16216     0.00     0.00  List<PayloadEntry>::getLen() const
  0.00      3.48     0.00     8936     0.00     0.00  ListNode<Entry*>::setNext(ListNode<Entry*>*)
  0.00      3.48     0.00     4890     0.00     0.00  isPrime(int)
  0.00      3.48     0.00     4158     0.00     0.00  EntryList::insert(Word*, PayloadEntry&, MatchType, unsigned int, Entry**)
  0.00      3.48     0.00     4069     0.00     0.00  HashTable::updateEntryPayload(Word*, PayloadEntry&, MatchType, unsigned int)
  0.00      3.48     0.00     4049     0.00     0.00  ListNode<PayloadEntry>::setNext(ListNode<PayloadEntry>*)
  0.00      3.48     0.00     2933     0.00     0.00  Scheduler::waitPendingMatchesFinish()
  0.00      3.48     0.00     2406     0.00     0.00  findNextPrime(int)
  0.00      3.48     0.00     2403     0.00     0.01  HashTable::deleteData()
  0.00      3.48     0.00     2402     0.00     0.03  scan(int, char const*, Word***, int*, int, int)
  0.00      3.48     0.00     2389     0.00     0.00  HashTable::~HashTable()
  0.00      3.48     0.00     2385     0.00     0.00  HashTable::HashTable(int, unsigned long (*)(char const*))
  0.00      3.48     0.00     2361     0.00     0.00  countSpaces(char const*)
  0.00      3.48     0.00     1920     0.00     0.00  Index::insert(Entry**)
  0.00      3.48     0.00     1920     0.00     0.00  Query::getMatchDist()
  0.00      3.48     0.00     1920     0.00     0.00  Query::getAdressOfActive()
  0.00      3.48     0.00     1920     0.00     0.00  Query::getType()
  0.00      3.48     0.00     1920     0.00     0.03  Query::Query(unsigned int, char const*, MatchType, unsigned int)
  0.00      3.48     0.00     1920     0.00     0.00  Query::~Query()
  0.00      3.48     0.00     1920     0.00     0.00  EntryList::insert(Query&, Entry***)
  0.00      3.48     0.00     1919     0.00     0.03  StartQuery
  0.00      3.48     0.00     1919     0.00     0.03  CoreWrapper::addQuery(unsigned int, char const*, MatchType, unsigned int)
  0.00      3.48     0.00     1919     0.00     0.00  Vector<Query*>::insertSorted(Query*&, int)
  0.00      3.48     0.00     1628     0.00     0.00  ListNode<Result*>::getNext() const
  0.00      3.48     0.00     1334     0.00     0.00  Queue<Result*>::getList()
  0.00      3.48     0.00     1312     0.00     0.00  List<Result*>::getLen() const
  0.00      3.48     0.00     1281     0.00     0.00  ArgClass::~ArgClass()
  0.00      3.48     0.00     1271     0.00     0.00  ArgClass::ArgClass(int, Scheduler*)
  0.00      3.48     0.00     1255     0.00     0.00  ArgClass::getSched()
  0.00      3.48     0.00     1253     0.00     0.00  ArgClass::getId()
  0.00      3.48     0.00     1067     0.00     0.00  List<PayloadEntry>::List(List<PayloadEntry> const&)
  0.00      3.48     0.00     1013     0.00     0.00  EndQuery
  0.00      3.48     0.00     1013     0.00     0.00  biSearchQuery(Vector<Query*>*, unsigned int)
  0.00      3.48     0.00     1013     0.00     0.00  CoreWrapper::deactivateQuery(unsigned int)
  0.00      3.48     0.00     1013     0.00     0.00  Query::deactivate()
  0.00      3.48     0.00      550     0.00     0.00  CoreWrapper::addResult(Result*)
  0.00      3.48     0.00      521     0.00     0.00  SearchArgs::~SearchArgs()
  0.00      3.48     0.00      514     0.00     0.00  ListNode<Result*>::~ListNode()
  0.00      3.48     0.00      509     0.00     0.00  Vector<Query*>::~Vector()
  0.00      3.48     0.00      507     0.00     0.00  ListNode<Result*>::ListNode(Result*&)
  0.00      3.48     0.00      503     0.00     0.00  ListNode<Result*>::getData()
  0.00      3.48     0.00      503     0.00     0.00  Scheduler::resMutexDown()
  0.00      3.48     0.00      495     0.00     0.00  Queue<Result*>::push(Result*&)
  0.00      3.48     0.00      495     0.00     0.00  List<Result*>::getItem(int) const
  0.00      3.48     0.00      490     0.00     0.00  Result::~Result()
  0.00      3.48     0.00      482     0.00     0.00  SearchArgs::~SearchArgs()
  0.00      3.48     0.00      481     0.00     0.00  List<Result*>::insert(Result*&, Result***)
  0.00      3.48     0.00      476     0.00     0.03  MatchDocument
  0.00      3.48     0.00      474     0.00     0.00  CoreWrapper::matchDocument(Document*)
  0.00      3.48     0.00      461     0.00     0.00  SearchArgs::getDocument()
  0.00      3.48     0.00      460     0.00     0.00  Result::fetch(unsigned int*, unsigned int*, unsigned int**)
  0.00      3.48     0.00      460     0.00     0.00  Scheduler::resMutexUp()
  0.00      3.48     0.00      454     0.00     0.00  Document::getWordsInDoc()
  0.00      3.48     0.00      450     0.00     0.00  List<Result*>::removeIdx(int)
  0.00      3.48     0.00      447     0.00     0.00  Queue<Result*>::pop()
  0.00      3.48     0.00      435     0.00     0.00  Document::getId()
  0.00      3.48     0.00      434     0.00     0.00  GetNextAvailRes
  0.00      3.48     0.00      431     0.00     0.00  SearchArgs::SearchArgs(Document*)
  0.00      3.48     0.00      430     0.00     0.04  Document::Document(unsigned int, char const*)
  0.00      3.48     0.00      424     0.00     0.00  Scheduler::waitForAvailRes()
  0.00      3.48     0.00      399     0.00     0.00  CoreWrapper::pullResult()
  0.00      3.48     0.00      112     0.00     0.09  BKTree::destroy(BKNode*)
  0.00      3.48     0.00      112     0.00     0.00  BKTree::BKTree(int (Word::*)(Word&))
  0.00      3.48     0.00      112     0.00     0.09  BKTree::~BKTree()
  0.00      3.48     0.00      108     0.00     0.00  Index::insert(Entry*)
  0.00      3.48     0.00       89     0.00     0.00  List<Entry>::insert(Entry&, Entry**)
  0.00      3.48     0.00       89     0.00     0.00  Entry::Entry(Entry&)
  0.00      3.48     0.00       89     0.00     0.00  ListNode<Entry>::getData()
  0.00      3.48     0.00       89     0.00     0.00  ListNode<Entry>::ListNode(Entry&)
  0.00      3.48     0.00       89     0.00     0.00  ListNode<Entry>::~ListNode()
  0.00      3.48     0.00       89     0.00     0.00  ListNode<Entry>::getNext() const
  0.00      3.48     0.00       88     0.00     0.00  ListNode<Entry>::setNext(ListNode<Entry>*)
  0.00      3.48     0.00       69     0.00     0.00  ListNode<Result*>::setNext(ListNode<Result*>*)
  0.00      3.48     0.00       67     0.00     0.00  BKNode::BKNode(Entry*, int)
  0.00      3.48     0.00       67     0.00     0.00  BKTree::insert(Entry*)
  0.00      3.48     0.00       67     0.00     0.00  BKTree::insert(BKNode**, Entry*, int)
  0.00      3.48     0.00       67     0.00     0.00  Vector<BKNode*>::Vector()
  0.00      3.48     0.00       67     0.00     0.00  Vector<BKNode*>::~Vector()
  0.00      3.48     0.00       48     0.00     0.00  Vector<BKNode*>::insert(BKNode*&)
  0.00      3.48     0.00        9     0.00     0.00  Index::Index(MatchType, int)
  0.00      3.48     0.00        9     0.00     1.11  Index::~Index()
  0.00      3.48     0.00        2     0.00     0.00  GetClockTimeInMilliSec()
  0.00      3.48     0.00        1     0.00    10.01  DestroyIndex
  0.00      3.48     0.00        1     0.00     0.00  InitializeIndex
  0.00      3.48     0.00        1     0.00     0.00  _GLOBAL__sub_I_CW
  0.00      3.48     0.00        1     0.00     0.00  _GLOBAL__sub_I__Z7isPrimei
  0.00      3.48     0.00        1     0.00     0.00  _GLOBAL__sub_I__ZN11CoreWrapperC2Ev
  0.00      3.48     0.00        1     0.00     0.00  _GLOBAL__sub_I__ZN12PayloadEntryC2EjPb
  0.00      3.48     0.00        1     0.00     0.00  _GLOBAL__sub_I__ZN4Args5printEv
  0.00      3.48     0.00        1     0.00     0.00  _GLOBAL__sub_I__ZN5EntryC2EPKcR12PayloadEntry9MatchTypej
  0.00      3.48     0.00        1     0.00     0.00  _GLOBAL__sub_I__ZN5IndexC2E9MatchTypei
  0.00      3.48     0.00        1     0.00     0.00  _GLOBAL__sub_I__ZN5QueryC2EjPKc9MatchTypej
  0.00      3.48     0.00        1     0.00     0.00  _GLOBAL__sub_I__ZN6BucketC2Ev
  0.00      3.48     0.00        1     0.00     0.00  _GLOBAL__sub_I__ZN6ResultC2EjR6VectorIP5QueryE
  0.00      3.48     0.00        1     0.00     0.00  _GLOBAL__sub_I__ZN8DocumentC2EjPKc
  0.00      3.48     0.00        1     0.00     0.00  _GLOBAL__sub_I__ZN9EntryListC2Ei
  0.00      3.48     0.00        1     0.00     0.00  _GLOBAL__sub_I__ZN9Scheduler24waitPendingMatchesFinishEv
  0.00      3.48     0.00        1     0.00    92.76  TestSigmod(char const*)
  0.00      3.48     0.00        1     0.00     0.00  __static_initialization_and_destruction_0(int, int)
  0.00      3.48     0.00        1     0.00     0.00  __static_initialization_and_destruction_0(int, int)
  0.00      3.48     0.00        1     0.00     0.00  __static_initialization_and_destruction_0(int, int)
  0.00      3.48     0.00        1     0.00     0.00  __static_initialization_and_destruction_0(int, int)
  0.00      3.48     0.00        1     0.00     0.00  __static_initialization_and_destruction_0(int, int)
  0.00      3.48     0.00        1     0.00     0.00  __static_initialization_and_destruction_0(int, int)
  0.00      3.48     0.00        1     0.00     0.00  __static_initialization_and_destruction_0(int, int)
  0.00      3.48     0.00        1     0.00     0.00  __static_initialization_and_destruction_0(int, int)
  0.00      3.48     0.00        1     0.00     0.00  __static_initialization_and_destruction_0(int, int)
  0.00      3.48     0.00        1     0.00     0.00  __static_initialization_and_destruction_0(int, int)
  0.00      3.48     0.00        1     0.00     0.00  __static_initialization_and_destruction_0(int, int)
  0.00      3.48     0.00        1     0.00     0.00  __static_initialization_and_destruction_0(int, int)
  0.00      3.48     0.00        1     0.00     0.00  __static_initialization_and_destruction_0(int, int)
  0.00      3.48     0.00        1     0.00     0.00  __static_initialization_and_destruction_0(int, int)
  0.00      3.48     0.00        1     0.00     0.00  __static_initialization_and_destruction_0(int, int)
  0.00      3.48     0.00        1     0.00     0.00  PrintTime(int)
  0.00      3.48     0.00        1     0.00     0.00  CoreWrapper::CoreWrapper()
  0.00      3.48     0.00        1     0.00    10.01  CoreWrapper::~CoreWrapper()
  0.00      3.48     0.00        1     0.00     0.00  List<Entry>::List()
  0.00      3.48     0.00        1     0.00     0.00  List<Entry>::~List()
  0.00      3.48     0.00        1     0.00     0.00  List<Job*>::List()
  0.00      3.48     0.00        1     0.00     0.00  List<Job*>::~List()
  0.00      3.48     0.00        1     0.00     0.00  List<Result*>::destroyData()
  0.00      3.48     0.00        1     0.00     0.00  List<Result*>::List()
  0.00      3.48     0.00        1     0.00     0.00  List<Result*>::~List()
  0.00      3.48     0.00        1     0.00     0.00  List<Document*>::destroyData()
  0.00      3.48     0.00        1     0.00     0.00  List<Document*>::List()
  0.00      3.48     0.00        1     0.00     0.00  List<Document*>::~List()
  0.00      3.48     0.00        1     0.00     0.00  Queue<Job*>::Queue()
  0.00      3.48     0.00        1     0.00     0.00  Queue<Job*>::~Queue()
  0.00      3.48     0.00        1     0.00     0.00  Queue<Result*>::destroyData()
  0.00      3.48     0.00        1     0.00     0.00  Queue<Result*>::Queue()
  0.00      3.48     0.00        1     0.00     0.00  Queue<Result*>::~Queue()
  0.00      3.48     0.00        1     0.00     0.00  Queue<Document*>::destroyData()
  0.00      3.48     0.00        1     0.00     0.00  Queue<Document*>::Queue()
  0.00      3.48     0.00        1     0.00     0.00  Queue<Document*>::~Queue()
  0.00      3.48     0.00        1     0.00     0.00  Vector<Query*>::destroyData()
  0.00      3.48     0.00        1     0.00     0.00  Vector<Query*>::Vector()
  0.00      3.48     0.00        1     0.00     0.00  EntryList::EntryList(int)
  0.00      3.48     0.00        1     0.00     0.00  EntryList::~EntryList()
  0.00      3.48     0.00        1     0.00     0.00  Scheduler::Scheduler(int)
  0.00      3.48     0.00        1     0.00     0.00  Scheduler::~Scheduler()

 %         the percentage of the total running time of the
time       program used by this function.

cumulative a running sum of the number of seconds accounted
 seconds   for by this function and those listed above it.

 self      the number of seconds accounted for by this
seconds    function alone.  This is the major sort for this
           listing.

calls      the number of times this function was invoked, if
           this function is profiled, else blank.

 self      the average number of milliseconds spent in this
ms/call    function per call, if this function is profiled,
	   else blank.

 total     the average number of milliseconds spent in this
ms/call    function and its descendents per call, if this
	   function is profiled, else blank.

name       the name of the function.  This is the minor sort
           for this listing. The index shows the location of
	   the function in the gprof listing. If the index is
	   in parenthesis it shows where it would appear in
	   the gprof listing if it were to be printed.

Copyright (C) 2012-2020 Free Software Foundation, Inc.

Copying and distribution of this file, with or without modification,
are permitted in any medium without royalty provided the copyright
notice and this notice are preserved.

		     Call graph (explanation follows)


granularity: each sample hit covers 2 byte(s) for 0.29% of 3.48 seconds

index % time    self  children    called     name
                                                 <spontaneous>
[1]     86.0    0.15    2.84                 doJobFunction(void*) [1]
                0.12    2.66 1934680/1934680     Scheduler::doJob(Job*, int) [2]
                0.02    0.01 1630904/1630904     Job::~Job() [37]
                0.03    0.00 3476668/3476799     checkCondition(pthread_mutex_t*, pthread_mutex_t*, bool*) [36]
                0.00    0.00    1280/1281        ArgClass::~ArgClass() [172]
                0.00    0.00    1254/1255        ArgClass::getSched() [174]
                0.00    0.00    1253/1253        ArgClass::getId() [175]
-----------------------------------------------
                0.12    2.66 1934680/1934680     doJobFunction(void*) [1]
[2]     79.9    0.12    2.66 1934680         Scheduler::doJob(Job*, int) [2]
                0.05    2.03 1732320/1732320     Index::search(Word*, int) [3]
                0.01    0.34 1667359/1667359     CoreWrapper::increaseCounter(List<Entry*>&, Result*, MatchType, unsigned int) [9]
                0.03    0.09  209132/209132      CoreWrapper::searchWordInIndeces(Word*, Result*, int) [13]
                0.03    0.01     450/450         Result::Result(unsigned int, Vector<Query*>&) [28]
                0.02    0.00 1745605/3665617     Job::getId() [26]
                0.02    0.00 1769313/1769313     SearchMethodArgs::getType() [54]
                0.02    0.00 1755649/1755649     SearchMethodArgs::getWord() [55]
                0.01    0.00 1653193/5511035     List<Entry*>::~List() [40]
                0.01    0.00  768996/4772702     Word::getLen() [27]
                0.01    0.00 1769907/1769907     SearchMethodArgs::getDist() [78]
                0.01    0.00 1767450/1767450     SearchMethodArgs::getParentIndex() [79]
                0.00    0.00 1767044/1767044     SearchMethodArgs::getRes() [118]
                0.00    0.00 1722323/1722323     Job::getArgs() [119]
                0.00    0.00  224990/224990      Document::getWord(int) [140]
                0.00    0.00     550/550         CoreWrapper::addResult(Result*) [177]
                0.00    0.00     485/1334        Queue<Result*>::getList() [170]
                0.00    0.00     474/1312        List<Result*>::getLen() const [171]
                0.00    0.00     461/461         SearchArgs::getDocument() [188]
                0.00    0.00     454/454         Document::getWordsInDoc() [190]
                0.00    0.00     435/435         Document::getId() [193]
-----------------------------------------------
                0.05    2.03 1732320/1732320     Scheduler::doJob(Job*, int) [2]
[3]     59.7    0.05    2.03 1732320         Index::search(Word*, int) [3]
                0.00    1.94 1517491/1517491     BKTree::search(Word*, int) [4]
                0.02    0.00 2499673/4772702     Word::getLen() [27]
                0.02    0.00 1493484/2433484     List<Entry*>::append(List<Entry*>*) [33]
                0.00    0.02  208588/629397      HashTable::getEntry(Word*) [22]
                0.01    0.00 1734163/4170434     List<Entry*>::List() [35]
                0.01    0.00 1469019/5511035     List<Entry*>::~List() [40]
                0.00    0.00     621/47264       List<Entry*>::insert(Entry*&, Entry***) [153]
-----------------------------------------------
                0.00    1.94 1517491/1517491     Index::search(Word*, int) [3]
[4]     55.8    0.00    1.94 1517491         BKTree::search(Word*, int) [4]
                0.15    1.76 1523557/1523557     BKTree::search(BKNode*, Word*, int) [5]
                0.02    0.00 1457018/1457018     List<Entry*>::List(List<Entry*> const&) [56]
                0.01    0.00 1503996/4772702     Word::getLen() [27]
                0.01    0.00 1450116/5511035     List<Entry*>::~List() [40]
-----------------------------------------------
                              946011             BKTree::search(BKNode*, Word*, int) [5]
                0.15    1.76 1523557/1523557     BKTree::search(Word*, int) [4]
[5]     54.8    0.15    1.76 1523557+946011  BKTree::search(BKNode*, Word*, int) [5]
                1.31    0.31 1071521/1071597     Word::editDist(Word&) [6]
                0.06    0.00  407244/407292      Word::hammingDist(Word&) [25]
                0.02    0.00 1383536/1383688     Vector<BKNode*>::getItem(int) const [48]
                0.02    0.00 2436271/4170434     List<Entry*>::List() [35]
                0.02    0.00 1434452/1434595     Vector<BKNode*>::getLen() const [57]
                0.01    0.00  940000/2433484     List<Entry*>::append(List<Entry*>*) [33]
                0.01    0.00 1524175/1524318     BKNode::getChildren() [72]
                0.01    0.00 1492663/2406559     Entry::getWord() [66]
                0.00    0.00  938707/5511035     List<Entry*>::~List() [40]
                0.00    0.00 1459802/1459926     BKNode::getData() [126]
                0.00    0.00 1397403/1397507     BKNode::getDist() [127]
                0.00    0.00   16306/47264       List<Entry*>::insert(Entry*&, Entry***) [153]
                              946011             BKTree::search(BKNode*, Word*, int) [5]
-----------------------------------------------
                0.00    0.00      27/1071597     BKTree::insert(Entry*) [94]
                0.00    0.00      49/1071597     BKTree::insert(BKNode**, Entry*, int) [95]
                1.31    0.31 1071521/1071597     BKTree::search(BKNode*, Word*, int) [5]
[6]     46.4    1.31    0.31 1071597         Word::editDist(Word&) [6]
                0.31    0.00 80917280/80917280     int const& std::min<int>(int const&, int const&) [10]
-----------------------------------------------
                                                 <spontaneous>
[7]     10.3    0.01    0.36                 giveJobFunction(void*) [7]
                0.24    0.12 1452273/1452273     Scheduler::assignJob() [8]
                0.00    0.00     131/3476799     checkCondition(pthread_mutex_t*, pthread_mutex_t*, bool*) [36]
                0.00    0.00 1579112/1579112     Queue<Job*>::getList() [123]
                0.00    0.00 1484212/1484212     List<Job*>::getLen() const [125]
                0.00    0.00       1/1255        ArgClass::getSched() [174]
                0.00    0.00       1/1281        ArgClass::~ArgClass() [172]
-----------------------------------------------
                0.24    0.12 1452273/1452273     giveJobFunction(void*) [7]
[8]     10.2    0.24    0.12 1452273         Scheduler::assignJob() [8]
                0.07    0.05 1699714/1699714     Queue<Job*>::pop() [12]
-----------------------------------------------
                0.01    0.34 1667359/1667359     Scheduler::doJob(Job*, int) [2]
[9]     10.0    0.01    0.34 1667359         CoreWrapper::increaseCounter(List<Entry*>&, Result*, MatchType, unsigned int) [9]
                0.03    0.18  419344/419344      Result::increaseCounter(unsigned int, Word*) [11]
                0.04    0.04  456434/456434      List<PayloadEntry>::getItem(int) const [17]
                0.04    0.00  463496/463496      PayloadEntry::getActive() [32]
                0.00    0.00 1639601/4092783     List<Entry*>::getLen() const [65]
                0.00    0.00  416489/2406559     Entry::getWord() [66]
                0.00    0.00  406457/406457      PayloadEntry::getId() [138]
                0.00    0.00   16357/46777       List<Entry*>::getItem(int) const [154]
                0.00    0.00   16352/16352       Entry::getPayload(MatchType, unsigned int) [155]
                0.00    0.00   16216/16216       List<PayloadEntry>::getLen() const [156]
-----------------------------------------------
                0.31    0.00 80917280/80917280     Word::editDist(Word&) [6]
[10]     8.8    0.31    0.00 80917280         int const& std::min<int>(int const&, int const&) [10]
-----------------------------------------------
                0.03    0.18  419344/419344      CoreWrapper::increaseCounter(List<Entry*>&, Result*, MatchType, unsigned int) [9]
[11]     6.1    0.03    0.18  419344         Result::increaseCounter(unsigned int, Word*) [11]
                0.06    0.06  407866/407866      biSearchQueryIndex(Vector<Query*>*, unsigned int) [14]
                0.04    0.00  648606/962629      Word::exactMatch(Word&) [24]
                0.03    0.00  652028/656185      Query::getWord(int) [38]
                0.00    0.00  394445/5643141     Vector<Query*>::getItem(int) const [43]
                0.00    0.00  393043/1137392     Query::getWordsInQuery() [128]
-----------------------------------------------
                0.07    0.05 1699714/1699714     Scheduler::assignJob() [8]
[12]     3.4    0.07    0.05 1699714         Queue<Job*>::pop() [12]
                0.02    0.02 1598464/1598464     List<Job*>::removeIdx(int) [30]
                0.01    0.00 1606898/1606898     List<Job*>::getItem(int) const [71]
-----------------------------------------------
                0.03    0.09  209132/209132      Scheduler::doJob(Job*, int) [2]
[13]     3.3    0.03    0.09  209132         CoreWrapper::searchWordInIndeces(Word*, Result*, int) [13]
                0.01    0.05 1886606/1887017     Scheduler::addJob(Job*) [23]
                0.02    0.00 1992770/1992770     SearchMethodArgs::SearchMethodArgs(Result*, Word*, int, int, int) [46]
                0.01    0.00 1935612/1936053     Job::Job(JobId, Args*) [68]
-----------------------------------------------
                0.06    0.06  407866/407866      Result::increaseCounter(unsigned int, Word*) [11]
[14]     3.3    0.06    0.06  407866         biSearchQueryIndex(Vector<Query*>*, unsigned int) [14]
                0.03    0.00 4484982/4539798     Query::getId() [34]
                0.02    0.00 4467432/5643141     Vector<Query*>::getItem(int) const [43]
                0.01    0.00  396372/398725      Vector<Query*>::getLen() const [73]
-----------------------------------------------
                                                 <spontaneous>
[15]     2.7    0.00    0.09                 main [15]
                0.00    0.09       1/1           TestSigmod(char const*) [16]
-----------------------------------------------
                0.00    0.09       1/1           main [15]
[16]     2.7    0.00    0.09       1         TestSigmod(char const*) [16]
                0.00    0.07    1919/1919        StartQuery [19]
                0.00    0.02     476/476         MatchDocument [52]
                0.00    0.01       1/1           DestroyIndex [60]
                0.00    0.00     434/434         GetNextAvailRes [82]
                0.00    0.00    1013/1013        EndQuery [90]
                0.00    0.00       2/2           GetClockTimeInMilliSec() [207]
                0.00    0.00       1/1           InitializeIndex [108]
                0.00    0.00       1/1           PrintTime(int) [236]
-----------------------------------------------
                0.04    0.04  456434/456434      CoreWrapper::increaseCounter(List<Entry*>&, Result*, MatchType, unsigned int) [9]
[17]     2.3    0.04    0.04  456434         List<PayloadEntry>::getItem(int) const [17]
                0.04    0.00 17522450/17725370     ListNode<PayloadEntry>::getNext() const [29]
                0.00    0.00  456831/456920      ListNode<PayloadEntry>::getData() [132]
-----------------------------------------------
                0.00    0.02     482/2402        Document::Document(unsigned int, char const*) [53]
                0.00    0.06    1920/2402        Query::Query(unsigned int, char const*, MatchType, unsigned int) [21]
[18]     2.3    0.00    0.08    2402         scan(int, char const*, Word***, int*, int, int) [18]
                0.00    0.04  412493/629397      HashTable::getEntry(Word*) [22]
                0.00    0.02  186330/186526      HashTable::insert(Entry*) [41]
                0.00    0.02    2403/2403        HashTable::deleteData() [42]
                0.00    0.00  429601/429601      Word::Word(char const*) [135]
                0.00    0.00  223058/424787      Word::~Word() [136]
                0.00    0.00  195436/408065      PayloadEntry::~PayloadEntry() [137]
                0.00    0.00  191101/193021      PayloadEntry::PayloadEntry(unsigned int, bool*) [145]
                0.00    0.00  187387/187476      Entry::Entry(Word&, PayloadEntry&, MatchType, unsigned int) [147]
                0.00    0.00    2396/2406        findNextPrime(int) [161]
                0.00    0.00    2379/2389        HashTable::~HashTable() [162]
                0.00    0.00    2375/2385        HashTable::HashTable(int, unsigned long (*)(char const*)) [163]
-----------------------------------------------
                0.00    0.07    1919/1919        TestSigmod(char const*) [16]
[19]     1.9    0.00    0.07    1919         StartQuery [19]
                0.00    0.07    1919/1919        CoreWrapper::addQuery(unsigned int, char const*, MatchType, unsigned int) [20]
-----------------------------------------------
                0.00    0.07    1919/1919        StartQuery [19]
[20]     1.9    0.00    0.07    1919         CoreWrapper::addQuery(unsigned int, char const*, MatchType, unsigned int) [20]
                0.00    0.06    1920/1920        Query::Query(unsigned int, char const*, MatchType, unsigned int) [21]
                0.00    0.00    1920/1920        EntryList::insert(Query&, Entry***) [84]
                0.00    0.00    1920/1920        Index::insert(Entry**) [86]
                0.00    0.00    1919/4539798     Query::getId() [34]
                0.00    0.00    1919/1919        Vector<Query*>::insertSorted(Query*&, int) [97]
                0.00    0.00    1919/2933        Scheduler::waitPendingMatchesFinish() [160]
-----------------------------------------------
                0.00    0.06    1920/1920        CoreWrapper::addQuery(unsigned int, char const*, MatchType, unsigned int) [20]
[21]     1.8    0.00    0.06    1920         Query::Query(unsigned int, char const*, MatchType, unsigned int) [21]
                0.00    0.06    1920/2402        scan(int, char const*, Word***, int*, int, int) [18]
                0.00    0.00    1920/2361        countSpaces(char const*) [164]
-----------------------------------------------
                0.00    0.00    4158/629397      Index::insert(Entry**) [86]
                0.00    0.00    4158/629397      EntryList::insert(Word*, PayloadEntry&, MatchType, unsigned int, Entry**) [85]
                0.00    0.02  208588/629397      Index::search(Word*, int) [3]
                0.00    0.04  412493/629397      scan(int, char const*, Word***, int*, int, int) [18]
[22]     1.7    0.00    0.06  629397         HashTable::getEntry(Word*) [22]
                0.03    0.00  631574/833034      djb2(char const*) [31]
                0.00    0.03  620877/624946      Bucket::getEntry(Word*) [39]
                0.00    0.00  621901/1678432     Word::getStr() [120]
-----------------------------------------------
                0.00    0.00     411/1887017     CoreWrapper::matchDocument(Document*) [96]
                0.01    0.05 1886606/1887017     CoreWrapper::searchWordInIndeces(Word*, Result*, int) [13]
[23]     1.6    0.01    0.05 1887017         Scheduler::addJob(Job*) [23]
                0.03    0.00 1920012/3665617     Job::getId() [26]
                0.00    0.02 2008926/2008926     Queue<Job*>::push(Job*&) [45]
-----------------------------------------------
                0.02    0.00  314023/962629      Bucket::getEntry(Word*) [39]
                0.04    0.00  648606/962629      Result::increaseCounter(unsigned int, Word*) [11]
[24]     1.6    0.06    0.00  962629         Word::exactMatch(Word&) [24]
                0.00    0.00  666384/1678432     Word::getStr() [120]
-----------------------------------------------
                0.00    0.00      21/407292      BKTree::insert(Entry*) [94]
                0.00    0.00      27/407292      BKTree::insert(BKNode**, Entry*, int) [95]
                0.06    0.00  407244/407292      BKTree::search(BKNode*, Word*, int) [5]
[25]     1.6    0.06    0.00  407292         Word::hammingDist(Word&) [25]
-----------------------------------------------
                0.02    0.00 1745605/3665617     Scheduler::doJob(Job*, int) [2]
                0.03    0.00 1920012/3665617     Scheduler::addJob(Job*) [23]
[26]     1.4    0.05    0.00 3665617         Job::getId() [26]
-----------------------------------------------
                0.00    0.00      37/4772702     Index::insert(Entry*) [93]
                0.01    0.00  768996/4772702     Scheduler::doJob(Job*, int) [2]
                0.01    0.00 1503996/4772702     BKTree::search(Word*, int) [4]
                0.02    0.00 2499673/4772702     Index::search(Word*, int) [3]
[27]     1.3    0.05    0.00 4772702         Word::getLen() [27]
-----------------------------------------------
                0.03    0.01     450/450         Scheduler::doJob(Job*, int) [2]
[28]     1.2    0.03    0.01     450         Result::Result(unsigned int, Vector<Query*>&) [28]
                0.01    0.00     414/414         Vector<Query*>::Vector(Vector<Query*> const&) [76]
                0.00    0.00  415309/5643141     Vector<Query*>::getItem(int) const [43]
                0.00    0.00     446/398725      Vector<Query*>::getLen() const [73]
                0.00    0.00  383009/1137392     Query::getWordsInQuery() [128]
-----------------------------------------------
                0.00    0.00      86/17725370     List<PayloadEntry>::List(List<PayloadEntry> const&) [107]
                0.00    0.00  202834/17725370     List<PayloadEntry>::~List() [87]
                0.04    0.00 17522450/17725370     List<PayloadEntry>::getItem(int) const [17]
[29]     1.1    0.04    0.00 17725370         ListNode<PayloadEntry>::getNext() const [29]
-----------------------------------------------
                0.02    0.02 1598464/1598464     Queue<Job*>::pop() [12]
[30]     1.1    0.02    0.02 1598464         List<Job*>::removeIdx(int) [30]
                0.02    0.00 1628222/1628222     ListNode<Job*>::~ListNode() [47]
                0.00    0.00 1621665/1621665     ListNode<Job*>::getNext() const [122]
-----------------------------------------------
                0.00    0.00    4068/833034      HashTable::updateEntryPayload(Word*, PayloadEntry&, MatchType, unsigned int) [89]
                0.01    0.00  197392/833034      HashTable::insert(Entry*) [41]
                0.03    0.00  631574/833034      HashTable::getEntry(Word*) [22]
[31]     1.1    0.04    0.00  833034         djb2(char const*) [31]
-----------------------------------------------
                0.04    0.00  463496/463496      CoreWrapper::increaseCounter(List<Entry*>&, Result*, MatchType, unsigned int) [9]
[32]     1.1    0.04    0.00  463496         PayloadEntry::getActive() [32]
-----------------------------------------------
                0.01    0.00  940000/2433484     BKTree::search(BKNode*, Word*, int) [5]
                0.02    0.00 1493484/2433484     Index::search(Word*, int) [3]
[33]     1.0    0.03    0.01 2433484         List<Entry*>::append(List<Entry*>*) [33]
                0.01    0.00 2453182/4092783     List<Entry*>::getLen() const [65]
                0.00    0.00   30420/46777       List<Entry*>::getItem(int) const [154]
                0.00    0.00   30337/47264       List<Entry*>::insert(Entry*&, Entry***) [153]
-----------------------------------------------
                0.00    0.00    1918/4539798     Vector<Query*>::insertSorted(Query*&, int) [97]
                0.00    0.00    1919/4539798     CoreWrapper::addQuery(unsigned int, char const*, MatchType, unsigned int) [20]
                0.00    0.00    1920/4539798     EntryList::insert(Query&, Entry***) [84]
                0.00    0.00   11546/4539798     biSearchQuery(Vector<Query*>*, unsigned int) [91]
                0.00    0.00   37513/4539798     Result::fetch(unsigned int*, unsigned int*, unsigned int**) [83]
                0.03    0.00 4484982/4539798     biSearchQueryIndex(Vector<Query*>*, unsigned int) [14]
[34]     0.9    0.03    0.00 4539798         Query::getId() [34]
-----------------------------------------------
                0.01    0.00 1734163/4170434     Index::search(Word*, int) [3]
                0.02    0.00 2436271/4170434     BKTree::search(BKNode*, Word*, int) [5]
[35]     0.9    0.03    0.00 4170434         List<Entry*>::List() [35]
-----------------------------------------------
                0.00    0.00     131/3476799     giveJobFunction(void*) [7]
                0.03    0.00 3476668/3476799     doJobFunction(void*) [1]
[36]     0.9    0.03    0.00 3476799         checkCondition(pthread_mutex_t*, pthread_mutex_t*, bool*) [36]
-----------------------------------------------
                0.02    0.01 1630904/1630904     doJobFunction(void*) [1]
[37]     0.9    0.02    0.01 1630904         Job::~Job() [37]
                0.00    0.01 1687707/1687707     SearchMethodArgs::~SearchMethodArgs() [70]
                0.00    0.00     521/521         SearchArgs::~SearchArgs() [178]
-----------------------------------------------
                0.00    0.00    4157/656185      EntryList::insert(Query&, Entry***) [84]
                0.03    0.00  652028/656185      Result::increaseCounter(unsigned int, Word*) [11]
[38]     0.9    0.03    0.00  656185         Query::getWord(int) [38]
-----------------------------------------------
                0.00    0.00    4069/624946      HashTable::updateEntryPayload(Word*, PayloadEntry&, MatchType, unsigned int) [89]
                0.00    0.03  620877/624946      HashTable::getEntry(Word*) [22]
[39]     0.8    0.00    0.03  624946         Bucket::getEntry(Word*) [39]
                0.02    0.00  314023/962629      Word::exactMatch(Word&) [24]
                0.01    0.00  683757/1329316     Vector<Entry*>::getLen() const [49]
                0.00    0.00  306273/2406559     Entry::getWord() [66]
                0.00    0.00  307783/507724      Vector<Entry*>::getItem(int) const [129]
-----------------------------------------------
                0.00    0.00  938707/5511035     BKTree::search(BKNode*, Word*, int) [5]
                0.01    0.00 1450116/5511035     BKTree::search(Word*, int) [4]
                0.01    0.00 1469019/5511035     Index::search(Word*, int) [3]
                0.01    0.00 1653193/5511035     Scheduler::doJob(Job*, int) [2]
[40]     0.7    0.03    0.00 5511035         List<Entry*>::~List() [40]
                0.00    0.00   63403/94326       ListNode<Entry*>::getNext() const [149]
                0.00    0.00   63213/63213       ListNode<Entry*>::~ListNode() [150]
-----------------------------------------------
                0.00    0.00      89/186526      EntryList::insert(Word*, PayloadEntry&, MatchType, unsigned int, Entry**) [85]
                0.00    0.00     107/186526      Index::insert(Entry**) [86]
                0.00    0.02  186330/186526      scan(int, char const*, Word***, int*, int, int) [18]
[41]     0.6    0.00    0.02  186526         HashTable::insert(Entry*) [41]
                0.00    0.01  191630/191630      Bucket::insert(Entry*) [74]
                0.01    0.00  197392/833034      djb2(char const*) [31]
                0.00    0.00  186602/2406559     Entry::getWord() [66]
                0.00    0.00  196885/1678432     Word::getStr() [120]
-----------------------------------------------
                0.00    0.02    2403/2403        scan(int, char const*, Word***, int*, int, int) [18]
[42]     0.6    0.00    0.02    2403         HashTable::deleteData() [42]
                0.01    0.01  438267/438267      Bucket::bucketSize() [51]
                0.00    0.00  200137/200137      Bucket::getEntry(int) [81]
                0.00    0.00  194819/194997      Entry::~Entry() [88]
-----------------------------------------------
                0.00    0.00   12559/5643141     biSearchQuery(Vector<Query*>*, unsigned int) [91]
                0.00    0.00  353396/5643141     Result::fetch(unsigned int*, unsigned int*, unsigned int**) [83]
                0.00    0.00  394445/5643141     Result::increaseCounter(unsigned int, Word*) [11]
                0.00    0.00  415309/5643141     Result::Result(unsigned int, Vector<Query*>&) [28]
                0.02    0.00 4467432/5643141     biSearchQueryIndex(Vector<Query*>*, unsigned int) [14]
[43]     0.6    0.02    0.00 5643141         Vector<Query*>::getItem(int) const [43]
-----------------------------------------------
                0.01    0.01 2020657/2020657     Queue<Job*>::push(Job*&) [45]
[44]     0.6    0.01    0.01 2020657         List<Job*>::insert(Job*&, Job***) [44]
                0.01    0.00 2039710/2039710     ListNode<Job*>::ListNode(Job*&) [67]
                0.00    0.00 1998648/1998648     ListNode<Job*>::setNext(ListNode<Job*>*) [116]
-----------------------------------------------
                0.00    0.02 2008926/2008926     Scheduler::addJob(Job*) [23]
[45]     0.6    0.00    0.02 2008926         Queue<Job*>::push(Job*&) [45]
                0.01    0.01 2020657/2020657     List<Job*>::insert(Job*&, Job***) [44]
-----------------------------------------------
                0.02    0.00 1992770/1992770     CoreWrapper::searchWordInIndeces(Word*, Result*, int) [13]
[46]     0.6    0.02    0.00 1992770         SearchMethodArgs::SearchMethodArgs(Result*, Word*, int, int, int) [46]
                0.00    0.00 1906188/1906623     Args::Args() [117]
-----------------------------------------------
                0.02    0.00 1628222/1628222     List<Job*>::removeIdx(int) [30]
[47]     0.6    0.02    0.00 1628222         ListNode<Job*>::~ListNode() [47]
-----------------------------------------------
                0.00    0.00      48/1383688     BKTree::destroy(BKNode*) [62]
                0.00    0.00     104/1383688     BKTree::insert(BKNode**, Entry*, int) [95]
                0.02    0.00 1383536/1383688     BKTree::search(BKNode*, Word*, int) [5]
[48]     0.6    0.02    0.00 1383688         Vector<BKNode*>::getItem(int) const [48]
-----------------------------------------------
                0.00    0.00  199703/1329316     Bucket::getEntry(int) [81]
                0.01    0.00  445856/1329316     Bucket::bucketSize() [51]
                0.01    0.00  683757/1329316     Bucket::getEntry(Word*) [39]
[49]     0.6    0.02    0.00 1329316         Vector<Entry*>::getLen() const [49]
-----------------------------------------------
                                                 <spontaneous>
[50]     0.6    0.00    0.02                 __libc_csu_init [50]
                0.02    0.00       1/1           _GLOBAL__sub_I__ZN4WordC2EPKc [58]
                0.01    0.00       1/1           _GLOBAL__sub_I__ZN6BKTreeC2EM4WordFiRS0_E [80]
                0.00    0.00       1/1           _GLOBAL__sub_I__ZN4Args5printEv [212]
                0.00    0.00       1/1           _GLOBAL__sub_I__ZN9Scheduler24waitPendingMatchesFinishEv [220]
                0.00    0.00       1/1           _GLOBAL__sub_I__ZN6ResultC2EjR6VectorIP5QueryE [217]
                0.00    0.00       1/1           _GLOBAL__sub_I__ZN8DocumentC2EjPKc [218]
                0.00    0.00       1/1           _GLOBAL__sub_I__ZN12PayloadEntryC2EjPb [211]
                0.00    0.00       1/1           _GLOBAL__sub_I_CW [208]
                0.00    0.00       1/1           _GLOBAL__sub_I__ZN11CoreWrapperC2Ev [210]
                0.00    0.00       1/1           _GLOBAL__sub_I__ZN9EntryListC2Ei [219]
                0.00    0.00       1/1           _GLOBAL__sub_I__Z7isPrimei [209]
                0.00    0.00       1/1           _GLOBAL__sub_I__ZN5IndexC2E9MatchTypei [214]
                0.00    0.00       1/1           _GLOBAL__sub_I__ZN5QueryC2EjPKc9MatchTypej [215]
                0.00    0.00       1/1           _GLOBAL__sub_I__ZN6BucketC2Ev [216]
                0.00    0.00       1/1           _GLOBAL__sub_I__ZN5EntryC2EPKcR12PayloadEntry9MatchTypej [213]
-----------------------------------------------
                0.01    0.01  438267/438267      HashTable::deleteData() [42]
[51]     0.5    0.01    0.01  438267         Bucket::bucketSize() [51]
                0.01    0.00  445856/1329316     Vector<Entry*>::getLen() const [49]
-----------------------------------------------
                0.00    0.02     476/476         TestSigmod(char const*) [16]
[52]     0.5    0.00    0.02     476         MatchDocument [52]
                0.00    0.02     430/430         Document::Document(unsigned int, char const*) [53]
                0.00    0.00     474/474         CoreWrapper::matchDocument(Document*) [96]
-----------------------------------------------
                0.00    0.02     430/430         MatchDocument [52]
[53]     0.5    0.00    0.02     430         Document::Document(unsigned int, char const*) [53]
                0.00    0.02     482/2402        scan(int, char const*, Word***, int*, int, int) [18]
                0.00    0.00     441/2361        countSpaces(char const*) [164]
-----------------------------------------------
                0.02    0.00 1769313/1769313     Scheduler::doJob(Job*, int) [2]
[54]     0.4    0.02    0.00 1769313         SearchMethodArgs::getType() [54]
-----------------------------------------------
                0.02    0.00 1755649/1755649     Scheduler::doJob(Job*, int) [2]
[55]     0.4    0.02    0.00 1755649         SearchMethodArgs::getWord() [55]
-----------------------------------------------
                0.02    0.00 1457018/1457018     BKTree::search(Word*, int) [4]
[56]     0.4    0.02    0.00 1457018         List<Entry*>::List(List<Entry*> const&) [56]
                0.00    0.00   22696/94326       ListNode<Entry*>::getNext() const [149]
                0.00    0.00   15796/61514       ListNode<Entry*>::ListNode(Entry*&) [152]
                0.00    0.00   15738/61606       ListNode<Entry*>::getData() [151]
                0.00    0.00    2346/8936        ListNode<Entry*>::setNext(ListNode<Entry*>*) [157]
-----------------------------------------------
                0.00    0.00      67/1434595     BKTree::destroy(BKNode*) [62]
                0.00    0.00      76/1434595     BKTree::insert(BKNode**, Entry*, int) [95]
                0.02    0.00 1434452/1434595     BKTree::search(BKNode*, Word*, int) [5]
[57]     0.4    0.02    0.00 1434595         Vector<BKNode*>::getLen() const [57]
-----------------------------------------------
                0.02    0.00       1/1           __libc_csu_init [50]
[58]     0.4    0.02    0.00       1         _GLOBAL__sub_I__ZN4WordC2EPKc [58]
                0.00    0.00       1/1           __static_initialization_and_destruction_0(int, int) [222]
-----------------------------------------------
                                                 <spontaneous>
[59]     0.4    0.02    0.00                 operator<<(std::ostream&, Word const&) [59]
-----------------------------------------------
                0.00    0.01       1/1           TestSigmod(char const*) [16]
[60]     0.3    0.00    0.01       1         DestroyIndex [60]
                0.00    0.01       1/1           CoreWrapper::~CoreWrapper() [61]
-----------------------------------------------
                0.00    0.01       1/1           DestroyIndex [60]
[61]     0.3    0.00    0.01       1         CoreWrapper::~CoreWrapper() [61]
                0.00    0.01       9/9           Index::~Index() [64]
                0.00    0.00       1/1           Queue<Result*>::destroyData() [100]
                0.00    0.00       1/1           EntryList::~EntryList() [106]
                0.00    0.00       1/2933        Scheduler::waitPendingMatchesFinish() [160]
                0.00    0.00       1/1           Vector<Query*>::destroyData() [253]
                0.00    0.00       1/509         Vector<Query*>::~Vector() [180]
                0.00    0.00       1/1           Queue<Document*>::destroyData() [250]
                0.00    0.00       1/1           Queue<Document*>::~Queue() [252]
                0.00    0.00       1/1           Queue<Result*>::~Queue() [249]
                0.00    0.00       1/1           Scheduler::~Scheduler() [257]
-----------------------------------------------
                                  48             BKTree::destroy(BKNode*) [62]
                0.00    0.01     112/112         BKTree::~BKTree() [63]
[62]     0.3    0.00    0.01     112+48      BKTree::destroy(BKNode*) [62]
                0.01    0.00      67/67          BKNode::~BKNode() [77]
                0.00    0.00      67/1434595     Vector<BKNode*>::getLen() const [57]
                0.00    0.00      48/1383688     Vector<BKNode*>::getItem(int) const [48]
                0.00    0.00      67/1524318     BKNode::getChildren() [72]
                                  48             BKTree::destroy(BKNode*) [62]
-----------------------------------------------
                0.00    0.01     112/112         Index::~Index() [64]
[63]     0.3    0.00    0.01     112         BKTree::~BKTree() [63]
                0.00    0.01     112/112         BKTree::destroy(BKNode*) [62]
-----------------------------------------------
                0.00    0.01       9/9           CoreWrapper::~CoreWrapper() [61]
[64]     0.3    0.00    0.01       9         Index::~Index() [64]
                0.00    0.01     112/112         BKTree::~BKTree() [63]
                0.00    0.00       9/2389        HashTable::~HashTable() [162]
-----------------------------------------------
                0.00    0.00 1639601/4092783     CoreWrapper::increaseCounter(List<Entry*>&, Result*, MatchType, unsigned int) [9]
                0.01    0.00 2453182/4092783     List<Entry*>::append(List<Entry*>*) [33]
[65]     0.3    0.01    0.00 4092783         List<Entry*>::getLen() const [65]
-----------------------------------------------
                0.00    0.00      37/2406559     Index::insert(Entry*) [93]
                0.00    0.00      89/2406559     Entry::Entry(Entry&) [102]
                0.00    0.00      96/2406559     BKTree::insert(Entry*) [94]
                0.00    0.00     152/2406559     BKTree::insert(BKNode**, Entry*, int) [95]
                0.00    0.00    4158/2406559     Index::insert(Entry**) [86]
                0.00    0.00  186602/2406559     HashTable::insert(Entry*) [41]
                0.00    0.00  306273/2406559     Bucket::getEntry(Word*) [39]
                0.00    0.00  416489/2406559     CoreWrapper::increaseCounter(List<Entry*>&, Result*, MatchType, unsigned int) [9]
                0.01    0.00 1492663/2406559     BKTree::search(BKNode*, Word*, int) [5]
[66]     0.3    0.01    0.00 2406559         Entry::getWord() [66]
-----------------------------------------------
                0.01    0.00 2039710/2039710     List<Job*>::insert(Job*&, Job***) [44]
[67]     0.3    0.01    0.00 2039710         ListNode<Job*>::ListNode(Job*&) [67]
-----------------------------------------------
                0.00    0.00     441/1936053     CoreWrapper::matchDocument(Document*) [96]
                0.01    0.00 1935612/1936053     CoreWrapper::searchWordInIndeces(Word*, Result*, int) [13]
[68]     0.3    0.01    0.00 1936053         Job::Job(JobId, Args*) [68]
-----------------------------------------------
                0.01    0.00 1693333/1693333     SearchMethodArgs::~SearchMethodArgs() [70]
[69]     0.3    0.01    0.00 1693333         SearchMethodArgs::~SearchMethodArgs() [69]
                0.00    0.00 1675013/1675490     Args::~Args() [121]
-----------------------------------------------
                0.00    0.01 1687707/1687707     Job::~Job() [37]
[70]     0.3    0.00    0.01 1687707         SearchMethodArgs::~SearchMethodArgs() [70]
                0.01    0.00 1693333/1693333     SearchMethodArgs::~SearchMethodArgs() [69]
-----------------------------------------------
                0.01    0.00 1606898/1606898     Queue<Job*>::pop() [12]
[71]     0.3    0.01    0.00 1606898         List<Job*>::getItem(int) const [71]
                0.00    0.00 1562015/1562015     ListNode<Job*>::getData() [124]
-----------------------------------------------
                0.00    0.00      67/1524318     BKTree::destroy(BKNode*) [62]
                0.00    0.00      76/1524318     BKTree::insert(BKNode**, Entry*, int) [95]
                0.01    0.00 1524175/1524318     BKTree::search(BKNode*, Word*, int) [5]
[72]     0.3    0.01    0.00 1524318         BKNode::getChildren() [72]
-----------------------------------------------
                0.00    0.00     426/398725      Result::fetch(unsigned int*, unsigned int*, unsigned int**) [83]
                0.00    0.00     446/398725      Result::Result(unsigned int, Vector<Query*>&) [28]
                0.00    0.00     468/398725      Result::~Result() [98]
                0.00    0.00    1013/398725      biSearchQuery(Vector<Query*>*, unsigned int) [91]
                0.01    0.00  396372/398725      biSearchQueryIndex(Vector<Query*>*, unsigned int) [14]
[73]     0.3    0.01    0.00  398725         Vector<Query*>::getLen() const [73]
-----------------------------------------------
                0.00    0.01  191630/191630      HashTable::insert(Entry*) [41]
[74]     0.3    0.00    0.01  191630         Bucket::insert(Entry*) [74]
                0.01    0.00  189998/189998      Vector<Entry*>::insert(Entry*&) [75]
-----------------------------------------------
                0.01    0.00  189998/189998      Bucket::insert(Entry*) [74]
[75]     0.3    0.01    0.00  189998         Vector<Entry*>::insert(Entry*&) [75]
-----------------------------------------------
                0.01    0.00     414/414         Result::Result(unsigned int, Vector<Query*>&) [28]
[76]     0.3    0.01    0.00     414         Vector<Query*>::Vector(Vector<Query*> const&) [76]
-----------------------------------------------
                0.01    0.00      67/67          BKTree::destroy(BKNode*) [62]
[77]     0.3    0.01    0.00      67         BKNode::~BKNode() [77]
                0.00    0.00      67/67          Vector<BKNode*>::~Vector() [204]
-----------------------------------------------
                0.01    0.00 1769907/1769907     Scheduler::doJob(Job*, int) [2]
[78]     0.1    0.01    0.00 1769907         SearchMethodArgs::getDist() [78]
-----------------------------------------------
                0.01    0.00 1767450/1767450     Scheduler::doJob(Job*, int) [2]
[79]     0.1    0.01    0.00 1767450         SearchMethodArgs::getParentIndex() [79]
-----------------------------------------------
                0.01    0.00       1/1           __libc_csu_init [50]
[80]     0.1    0.01    0.00       1         _GLOBAL__sub_I__ZN6BKTreeC2EM4WordFiRS0_E [80]
                0.00    0.00       1/1           __static_initialization_and_destruction_0(int, int) [225]
-----------------------------------------------
                0.00    0.00  200137/200137      HashTable::deleteData() [42]
[81]     0.1    0.00    0.00  200137         Bucket::getEntry(int) [81]
                0.00    0.00  199703/1329316     Vector<Entry*>::getLen() const [49]
                0.00    0.00  199941/507724      Vector<Entry*>::getItem(int) const [129]
-----------------------------------------------
                0.00    0.00     434/434         TestSigmod(char const*) [16]
[82]     0.0    0.00    0.00     434         GetNextAvailRes [82]
                0.00    0.00     460/460         Result::fetch(unsigned int*, unsigned int*, unsigned int**) [83]
                0.00    0.00     442/490         Result::~Result() [98]
                0.00    0.00     399/399         CoreWrapper::pullResult() [196]
-----------------------------------------------
                0.00    0.00     460/460         GetNextAvailRes [82]
[83]     0.0    0.00    0.00     460         Result::fetch(unsigned int*, unsigned int*, unsigned int**) [83]
                0.00    0.00  353396/5643141     Vector<Query*>::getItem(int) const [43]
                0.00    0.00   37513/4539798     Query::getId() [34]
                0.00    0.00     426/398725      Vector<Query*>::getLen() const [73]
                0.00    0.00  371280/371280      satisfy(bool*, int) [139]
                0.00    0.00  359420/1137392     Query::getWordsInQuery() [128]
-----------------------------------------------
                0.00    0.00    1920/1920        CoreWrapper::addQuery(unsigned int, char const*, MatchType, unsigned int) [20]
[84]     0.0    0.00    0.00    1920         EntryList::insert(Query&, Entry***) [84]
                0.00    0.00    4158/4158        EntryList::insert(Word*, PayloadEntry&, MatchType, unsigned int, Entry**) [85]
                0.00    0.00    4157/656185      Query::getWord(int) [38]
                0.00    0.00    1920/4539798     Query::getId() [34]
                0.00    0.00    1920/1137392     Query::getWordsInQuery() [128]
                0.00    0.00    1920/1920        Query::getAdressOfActive() [166]
                0.00    0.00    1920/193021      PayloadEntry::PayloadEntry(unsigned int, bool*) [145]
                0.00    0.00    1920/1920        Query::getType() [167]
                0.00    0.00    1920/1920        Query::getMatchDist() [165]
                0.00    0.00    1920/408065      PayloadEntry::~PayloadEntry() [137]
-----------------------------------------------
                0.00    0.00    4158/4158        EntryList::insert(Query&, Entry***) [84]
[85]     0.0    0.00    0.00    4158         EntryList::insert(Word*, PayloadEntry&, MatchType, unsigned int, Entry**) [85]
                0.00    0.00    4158/629397      HashTable::getEntry(Word*) [22]
                0.00    0.00    4069/4069        HashTable::updateEntryPayload(Word*, PayloadEntry&, MatchType, unsigned int) [89]
                0.00    0.00      89/186526      HashTable::insert(Entry*) [41]
                0.00    0.00      89/89          List<Entry>::insert(Entry&, Entry**) [101]
                0.00    0.00      89/194997      Entry::~Entry() [88]
                0.00    0.00      89/187476      Entry::Entry(Word&, PayloadEntry&, MatchType, unsigned int) [147]
-----------------------------------------------
                0.00    0.00    1920/1920        CoreWrapper::addQuery(unsigned int, char const*, MatchType, unsigned int) [20]
[86]     0.0    0.00    0.00    1920         Index::insert(Entry**) [86]
                0.00    0.00    4158/629397      HashTable::getEntry(Word*) [22]
                0.00    0.00     108/108         Index::insert(Entry*) [93]
                0.00    0.00    4158/2406559     Entry::getWord() [66]
                0.00    0.00     107/186526      HashTable::insert(Entry*) [41]
-----------------------------------------------
                0.00    0.00 2388260/2388260     Entry::~Entry() [88]
[87]     0.0    0.00    0.00 2388260         List<PayloadEntry>::~List() [87]
                0.00    0.00  202834/17725370     ListNode<PayloadEntry>::getNext() const [29]
                0.00    0.00  205482/205482      ListNode<PayloadEntry>::~ListNode() [141]
-----------------------------------------------
                0.00    0.00      89/194997      EntryList::insert(Word*, PayloadEntry&, MatchType, unsigned int, Entry**) [85]
                0.00    0.00      89/194997      ListNode<Entry>::~ListNode() [104]
                0.00    0.00  194819/194997      HashTable::deleteData() [42]
[88]     0.0    0.00    0.00  194997         Entry::~Entry() [88]
                0.00    0.00 2388260/2388260     List<PayloadEntry>::~List() [87]
                0.00    0.00  197571/424787      Word::~Word() [136]
-----------------------------------------------
                0.00    0.00    4069/4069        EntryList::insert(Word*, PayloadEntry&, MatchType, unsigned int, Entry**) [85]
[89]     0.0    0.00    0.00    4069         HashTable::updateEntryPayload(Word*, PayloadEntry&, MatchType, unsigned int) [89]
                0.00    0.00    4068/833034      djb2(char const*) [31]
                0.00    0.00    4069/624946      Bucket::getEntry(Word*) [39]
                0.00    0.00    4069/194170      Entry::addToPayload(PayloadEntry&, MatchType, unsigned int) [144]
                0.00    0.00    4068/1678432     Word::getStr() [120]
-----------------------------------------------
                0.00    0.00    1013/1013        TestSigmod(char const*) [16]
[90]     0.0    0.00    0.00    1013         EndQuery [90]
                0.00    0.00    1013/1013        CoreWrapper::deactivateQuery(unsigned int) [92]
-----------------------------------------------
                0.00    0.00    1013/1013        CoreWrapper::deactivateQuery(unsigned int) [92]
[91]     0.0    0.00    0.00    1013         biSearchQuery(Vector<Query*>*, unsigned int) [91]
                0.00    0.00   11546/4539798     Query::getId() [34]
                0.00    0.00   12559/5643141     Vector<Query*>::getItem(int) const [43]
                0.00    0.00    1013/398725      Vector<Query*>::getLen() const [73]
-----------------------------------------------
                0.00    0.00    1013/1013        EndQuery [90]
[92]     0.0    0.00    0.00    1013         CoreWrapper::deactivateQuery(unsigned int) [92]
                0.00    0.00    1013/1013        biSearchQuery(Vector<Query*>*, unsigned int) [91]
                0.00    0.00    1013/1013        Query::deactivate() [176]
                0.00    0.00    1013/2933        Scheduler::waitPendingMatchesFinish() [160]
-----------------------------------------------
                0.00    0.00     108/108         Index::insert(Entry**) [86]
[93]     0.0    0.00    0.00     108         Index::insert(Entry*) [93]
                0.00    0.00      67/67          BKTree::insert(Entry*) [94]
                0.00    0.00      37/4772702     Word::getLen() [27]
                0.00    0.00      37/2406559     Entry::getWord() [66]
-----------------------------------------------
                0.00    0.00      67/67          Index::insert(Entry*) [93]
[94]     0.0    0.00    0.00      67         BKTree::insert(Entry*) [94]
                0.00    0.00      67/67          BKTree::insert(BKNode**, Entry*, int) [95]
                0.00    0.00      27/1071597     Word::editDist(Word&) [6]
                0.00    0.00      21/407292      Word::hammingDist(Word&) [25]
                0.00    0.00      96/2406559     Entry::getWord() [66]
                0.00    0.00      48/1459926     BKNode::getData() [126]
-----------------------------------------------
                                  76             BKTree::insert(BKNode**, Entry*, int) [95]
                0.00    0.00      67/67          BKTree::insert(Entry*) [94]
[95]     0.0    0.00    0.00      67+76      BKTree::insert(BKNode**, Entry*, int) [95]
                0.00    0.00      49/1071597     Word::editDist(Word&) [6]
                0.00    0.00      27/407292      Word::hammingDist(Word&) [25]
                0.00    0.00     104/1383688     Vector<BKNode*>::getItem(int) const [48]
                0.00    0.00      76/1434595     Vector<BKNode*>::getLen() const [57]
                0.00    0.00     152/2406559     Entry::getWord() [66]
                0.00    0.00      76/1524318     BKNode::getChildren() [72]
                0.00    0.00     104/1397507     BKNode::getDist() [127]
                0.00    0.00      76/1459926     BKNode::getData() [126]
                0.00    0.00      67/67          BKNode::BKNode(Entry*, int) [202]
                0.00    0.00      48/48          Vector<BKNode*>::insert(BKNode*&) [205]
                                  76             BKTree::insert(BKNode**, Entry*, int) [95]
-----------------------------------------------
                0.00    0.00     474/474         MatchDocument [52]
[96]     0.0    0.00    0.00     474         CoreWrapper::matchDocument(Document*) [96]
                0.00    0.00     411/1887017     Scheduler::addJob(Job*) [23]
                0.00    0.00     441/1936053     Job::Job(JobId, Args*) [68]
                0.00    0.00     431/431         SearchArgs::SearchArgs(Document*) [194]
-----------------------------------------------
                0.00    0.00    1919/1919        CoreWrapper::addQuery(unsigned int, char const*, MatchType, unsigned int) [20]
[97]     0.0    0.00    0.00    1919         Vector<Query*>::insertSorted(Query*&, int) [97]
                0.00    0.00    1918/4539798     Query::getId() [34]
-----------------------------------------------
                0.00    0.00      48/490         List<Result*>::destroyData() [99]
                0.00    0.00     442/490         GetNextAvailRes [82]
[98]     0.0    0.00    0.00     490         Result::~Result() [98]
                0.00    0.00     468/398725      Vector<Query*>::getLen() const [73]
                0.00    0.00     508/509         Vector<Query*>::~Vector() [180]
-----------------------------------------------
                0.00    0.00       1/1           Queue<Result*>::destroyData() [100]
[99]     0.0    0.00    0.00       1         List<Result*>::destroyData() [99]
                0.00    0.00      48/490         Result::~Result() [98]
                0.00    0.00      48/495         List<Result*>::getItem(int) const [185]
-----------------------------------------------
                0.00    0.00       1/1           CoreWrapper::~CoreWrapper() [61]
[100]    0.0    0.00    0.00       1         Queue<Result*>::destroyData() [100]
                0.00    0.00       1/1           List<Result*>::destroyData() [99]
-----------------------------------------------
                0.00    0.00      89/89          EntryList::insert(Word*, PayloadEntry&, MatchType, unsigned int, Entry**) [85]
[101]    0.0    0.00    0.00      89         List<Entry>::insert(Entry&, Entry**) [101]
                0.00    0.00      89/89          ListNode<Entry>::ListNode(Entry&) [103]
                0.00    0.00      89/89          ListNode<Entry>::getData() [198]
                0.00    0.00      88/88          ListNode<Entry>::setNext(ListNode<Entry>*) [200]
-----------------------------------------------
                0.00    0.00      89/89          ListNode<Entry>::ListNode(Entry&) [103]
[102]    0.0    0.00    0.00      89         Entry::Entry(Entry&) [102]
                0.00    0.00      89/2406559     Entry::getWord() [66]
                0.00    0.00    1067/1067        List<PayloadEntry>::List(List<PayloadEntry> const&) [107]
                0.00    0.00      89/184970      Word::Word(Word&) [148]
-----------------------------------------------
                0.00    0.00      89/89          List<Entry>::insert(Entry&, Entry**) [101]
[103]    0.0    0.00    0.00      89         ListNode<Entry>::ListNode(Entry&) [103]
                0.00    0.00      89/89          Entry::Entry(Entry&) [102]
-----------------------------------------------
                0.00    0.00      89/89          List<Entry>::~List() [105]
[104]    0.0    0.00    0.00      89         ListNode<Entry>::~ListNode() [104]
                0.00    0.00      89/194997      Entry::~Entry() [88]
-----------------------------------------------
                0.00    0.00       1/1           EntryList::~EntryList() [106]
[105]    0.0    0.00    0.00       1         List<Entry>::~List() [105]
                0.00    0.00      89/89          ListNode<Entry>::~ListNode() [104]
                0.00    0.00      89/89          ListNode<Entry>::getNext() const [199]
-----------------------------------------------
                0.00    0.00       1/1           CoreWrapper::~CoreWrapper() [61]
[106]    0.0    0.00    0.00       1         EntryList::~EntryList() [106]
                0.00    0.00       1/1           List<Entry>::~List() [105]
                0.00    0.00       1/2389        HashTable::~HashTable() [162]
-----------------------------------------------
                0.00    0.00    1067/1067        Entry::Entry(Entry&) [102]
[107]    0.0    0.00    0.00    1067         List<PayloadEntry>::List(List<PayloadEntry> const&) [107]
                0.00    0.00      86/17725370     ListNode<PayloadEntry>::getNext() const [29]
                0.00    0.00      89/456920      ListNode<PayloadEntry>::getData() [132]
                0.00    0.00      86/199134      ListNode<PayloadEntry>::ListNode(PayloadEntry&) [142]
-----------------------------------------------
                0.00    0.00       1/1           TestSigmod(char const*) [16]
[108]    0.0    0.00    0.00       1         InitializeIndex [108]
                0.00    0.00       1/1           CoreWrapper::CoreWrapper() [237]
-----------------------------------------------
                0.00    0.00 2267835/2267835     Entry::Entry(Word&, PayloadEntry&, MatchType, unsigned int) [147]
[115]    0.0    0.00    0.00 2267835         List<PayloadEntry>::List() [115]
-----------------------------------------------
                0.00    0.00 1998648/1998648     List<Job*>::insert(Job*&, Job***) [44]
[116]    0.0    0.00    0.00 1998648         ListNode<Job*>::setNext(ListNode<Job*>*) [116]
-----------------------------------------------
                0.00    0.00     435/1906623     SearchArgs::SearchArgs(Document*) [194]
                0.00    0.00 1906188/1906623     SearchMethodArgs::SearchMethodArgs(Result*, Word*, int, int, int) [46]
[117]    0.0    0.00    0.00 1906623         Args::Args() [117]
-----------------------------------------------
                0.00    0.00 1767044/1767044     Scheduler::doJob(Job*, int) [2]
[118]    0.0    0.00    0.00 1767044         SearchMethodArgs::getRes() [118]
-----------------------------------------------
                0.00    0.00 1722323/1722323     Scheduler::doJob(Job*, int) [2]
[119]    0.0    0.00    0.00 1722323         Job::getArgs() [119]
-----------------------------------------------
                0.00    0.00    4068/1678432     HashTable::updateEntryPayload(Word*, PayloadEntry&, MatchType, unsigned int) [89]
                0.00    0.00  189194/1678432     Word::Word(Word&) [148]
                0.00    0.00  196885/1678432     HashTable::insert(Entry*) [41]
                0.00    0.00  621901/1678432     HashTable::getEntry(Word*) [22]
                0.00    0.00  666384/1678432     Word::exactMatch(Word&) [24]
[120]    0.0    0.00    0.00 1678432         Word::getStr() [120]
-----------------------------------------------
                0.00    0.00     477/1675490     SearchArgs::~SearchArgs() [186]
                0.00    0.00 1675013/1675490     SearchMethodArgs::~SearchMethodArgs() [69]
[121]    0.0    0.00    0.00 1675490         Args::~Args() [121]
-----------------------------------------------
                0.00    0.00 1621665/1621665     List<Job*>::removeIdx(int) [30]
[122]    0.0    0.00    0.00 1621665         ListNode<Job*>::getNext() const [122]
-----------------------------------------------
                0.00    0.00 1579112/1579112     giveJobFunction(void*) [7]
[123]    0.0    0.00    0.00 1579112         Queue<Job*>::getList() [123]
-----------------------------------------------
                0.00    0.00 1562015/1562015     List<Job*>::getItem(int) const [71]
[124]    0.0    0.00    0.00 1562015         ListNode<Job*>::getData() [124]
-----------------------------------------------
                0.00    0.00 1484212/1484212     giveJobFunction(void*) [7]
[125]    0.0    0.00    0.00 1484212         List<Job*>::getLen() const [125]
-----------------------------------------------
                0.00    0.00      48/1459926     BKTree::insert(Entry*) [94]
                0.00    0.00      76/1459926     BKTree::insert(BKNode**, Entry*, int) [95]
                0.00    0.00 1459802/1459926     BKTree::search(BKNode*, Word*, int) [5]
[126]    0.0    0.00    0.00 1459926         BKNode::getData() [126]
-----------------------------------------------
                0.00    0.00     104/1397507     BKTree::insert(BKNode**, Entry*, int) [95]
                0.00    0.00 1397403/1397507     BKTree::search(BKNode*, Word*, int) [5]
[127]    0.0    0.00    0.00 1397507         BKNode::getDist() [127]
-----------------------------------------------
                0.00    0.00    1920/1137392     EntryList::insert(Query&, Entry***) [84]
                0.00    0.00  359420/1137392     Result::fetch(unsigned int*, unsigned int*, unsigned int**) [83]
                0.00    0.00  383009/1137392     Result::Result(unsigned int, Vector<Query*>&) [28]
                0.00    0.00  393043/1137392     Result::increaseCounter(unsigned int, Word*) [11]
[128]    0.0    0.00    0.00 1137392         Query::getWordsInQuery() [128]
-----------------------------------------------
                0.00    0.00  199941/507724      Bucket::getEntry(int) [81]
                0.00    0.00  307783/507724      Bucket::getEntry(Word*) [39]
[129]    0.0    0.00    0.00  507724         Vector<Entry*>::getItem(int) const [129]
-----------------------------------------------
                0.00    0.00  471340/471340      Bucket::Bucket() [131]
[130]    0.0    0.00    0.00  471340         Vector<Entry*>::Vector() [130]
-----------------------------------------------
                0.00    0.00  466087/466087      HashTable::HashTable(int, unsigned long (*)(char const*)) [163]
[131]    0.0    0.00    0.00  466087         Bucket::Bucket() [131]
                0.00    0.00  471340/471340      Vector<Entry*>::Vector() [130]
-----------------------------------------------
                0.00    0.00      89/456920      List<PayloadEntry>::List(List<PayloadEntry> const&) [107]
                0.00    0.00  456831/456920      List<PayloadEntry>::getItem(int) const [17]
[132]    0.0    0.00    0.00  456920         ListNode<PayloadEntry>::getData() [132]
-----------------------------------------------
                0.00    0.00  454670/454670      Bucket::~Bucket() [134]
[133]    0.0    0.00    0.00  454670         Vector<Entry*>::~Vector() [133]
-----------------------------------------------
                0.00    0.00  450610/450610      HashTable::~HashTable() [162]
[134]    0.0    0.00    0.00  450610         Bucket::~Bucket() [134]
                0.00    0.00  454670/454670      Vector<Entry*>::~Vector() [133]
-----------------------------------------------
                0.00    0.00  429601/429601      scan(int, char const*, Word***, int*, int, int) [18]
[135]    0.0    0.00    0.00  429601         Word::Word(char const*) [135]
-----------------------------------------------
                0.00    0.00    4158/424787      Query::~Query() [168]
                0.00    0.00  197571/424787      Entry::~Entry() [88]
                0.00    0.00  223058/424787      scan(int, char const*, Word***, int*, int, int) [18]
[136]    0.0    0.00    0.00  424787         Word::~Word() [136]
-----------------------------------------------
                0.00    0.00    1920/408065      EntryList::insert(Query&, Entry***) [84]
                0.00    0.00  195436/408065      scan(int, char const*, Word***, int*, int, int) [18]
                0.00    0.00  210709/408065      ListNode<PayloadEntry>::~ListNode() [141]
[137]    0.0    0.00    0.00  408065         PayloadEntry::~PayloadEntry() [137]
-----------------------------------------------
                0.00    0.00  406457/406457      CoreWrapper::increaseCounter(List<Entry*>&, Result*, MatchType, unsigned int) [9]
[138]    0.0    0.00    0.00  406457         PayloadEntry::getId() [138]
-----------------------------------------------
                0.00    0.00  371280/371280      Result::fetch(unsigned int*, unsigned int*, unsigned int**) [83]
[139]    0.0    0.00    0.00  371280         satisfy(bool*, int) [139]
-----------------------------------------------
                0.00    0.00  224990/224990      Scheduler::doJob(Job*, int) [2]
[140]    0.0    0.00    0.00  224990         Document::getWord(int) [140]
-----------------------------------------------
                0.00    0.00  205482/205482      List<PayloadEntry>::~List() [87]
[141]    0.0    0.00    0.00  205482         ListNode<PayloadEntry>::~ListNode() [141]
                0.00    0.00  210709/408065      PayloadEntry::~PayloadEntry() [137]
-----------------------------------------------
                0.00    0.00      86/199134      List<PayloadEntry>::List(List<PayloadEntry> const&) [107]
                0.00    0.00  199048/199134      List<PayloadEntry>::insert(PayloadEntry&, PayloadEntry**) [146]
[142]    0.0    0.00    0.00  199134         ListNode<PayloadEntry>::ListNode(PayloadEntry&) [142]
                0.00    0.00  196859/196859      PayloadEntry::PayloadEntry(PayloadEntry&) [143]
-----------------------------------------------
                0.00    0.00  196859/196859      ListNode<PayloadEntry>::ListNode(PayloadEntry&) [142]
[143]    0.0    0.00    0.00  196859         PayloadEntry::PayloadEntry(PayloadEntry&) [143]
-----------------------------------------------
                0.00    0.00    4069/194170      HashTable::updateEntryPayload(Word*, PayloadEntry&, MatchType, unsigned int) [89]
                0.00    0.00  190101/194170      Entry::Entry(Word&, PayloadEntry&, MatchType, unsigned int) [147]
[144]    0.0    0.00    0.00  194170         Entry::addToPayload(PayloadEntry&, MatchType, unsigned int) [144]
                0.00    0.00  192346/192346      List<PayloadEntry>::insert(PayloadEntry&, PayloadEntry**) [146]
-----------------------------------------------
                0.00    0.00    1920/193021      EntryList::insert(Query&, Entry***) [84]
                0.00    0.00  191101/193021      scan(int, char const*, Word***, int*, int, int) [18]
[145]    0.0    0.00    0.00  193021         PayloadEntry::PayloadEntry(unsigned int, bool*) [145]
-----------------------------------------------
                0.00    0.00  192346/192346      Entry::addToPayload(PayloadEntry&, MatchType, unsigned int) [144]
[146]    0.0    0.00    0.00  192346         List<PayloadEntry>::insert(PayloadEntry&, PayloadEntry**) [146]
                0.00    0.00  199048/199134      ListNode<PayloadEntry>::ListNode(PayloadEntry&) [142]
                0.00    0.00    4049/4049        ListNode<PayloadEntry>::setNext(ListNode<PayloadEntry>*) [159]
-----------------------------------------------
                0.00    0.00      89/187476      EntryList::insert(Word*, PayloadEntry&, MatchType, unsigned int, Entry**) [85]
                0.00    0.00  187387/187476      scan(int, char const*, Word***, int*, int, int) [18]
[147]    0.0    0.00    0.00  187476         Entry::Entry(Word&, PayloadEntry&, MatchType, unsigned int) [147]
                0.00    0.00 2267835/2267835     List<PayloadEntry>::List() [115]
                0.00    0.00  190101/194170      Entry::addToPayload(PayloadEntry&, MatchType, unsigned int) [144]
                0.00    0.00  184881/184970      Word::Word(Word&) [148]
-----------------------------------------------
                0.00    0.00      89/184970      Entry::Entry(Entry&) [102]
                0.00    0.00  184881/184970      Entry::Entry(Word&, PayloadEntry&, MatchType, unsigned int) [147]
[148]    0.0    0.00    0.00  184970         Word::Word(Word&) [148]
                0.00    0.00  189194/1678432     Word::getStr() [120]
-----------------------------------------------
                0.00    0.00    8227/94326       List<Entry*>::getItem(int) const [154]
                0.00    0.00   22696/94326       List<Entry*>::List(List<Entry*> const&) [56]
                0.00    0.00   63403/94326       List<Entry*>::~List() [40]
[149]    0.0    0.00    0.00   94326         ListNode<Entry*>::getNext() const [149]
-----------------------------------------------
                0.00    0.00   63213/63213       List<Entry*>::~List() [40]
[150]    0.0    0.00    0.00   63213         ListNode<Entry*>::~ListNode() [150]
-----------------------------------------------
                0.00    0.00   15738/61606       List<Entry*>::List(List<Entry*> const&) [56]
                0.00    0.00   45868/61606       List<Entry*>::getItem(int) const [154]
[151]    0.0    0.00    0.00   61606         ListNode<Entry*>::getData() [151]
-----------------------------------------------
                0.00    0.00   15796/61514       List<Entry*>::List(List<Entry*> const&) [56]
                0.00    0.00   45718/61514       List<Entry*>::insert(Entry*&, Entry***) [153]
[152]    0.0    0.00    0.00   61514         ListNode<Entry*>::ListNode(Entry*&) [152]
-----------------------------------------------
                0.00    0.00     621/47264       Index::search(Word*, int) [3]
                0.00    0.00   16306/47264       BKTree::search(BKNode*, Word*, int) [5]
                0.00    0.00   30337/47264       List<Entry*>::append(List<Entry*>*) [33]
[153]    0.0    0.00    0.00   47264         List<Entry*>::insert(Entry*&, Entry***) [153]
                0.00    0.00   45718/61514       ListNode<Entry*>::ListNode(Entry*&) [152]
                0.00    0.00    6590/8936        ListNode<Entry*>::setNext(ListNode<Entry*>*) [157]
-----------------------------------------------
                0.00    0.00   16357/46777       CoreWrapper::increaseCounter(List<Entry*>&, Result*, MatchType, unsigned int) [9]
                0.00    0.00   30420/46777       List<Entry*>::append(List<Entry*>*) [33]
[154]    0.0    0.00    0.00   46777         List<Entry*>::getItem(int) const [154]
                0.00    0.00   45868/61606       ListNode<Entry*>::getData() [151]
                0.00    0.00    8227/94326       ListNode<Entry*>::getNext() const [149]
-----------------------------------------------
                0.00    0.00   16352/16352       CoreWrapper::increaseCounter(List<Entry*>&, Result*, MatchType, unsigned int) [9]
[155]    0.0    0.00    0.00   16352         Entry::getPayload(MatchType, unsigned int) [155]
-----------------------------------------------
                0.00    0.00   16216/16216       CoreWrapper::increaseCounter(List<Entry*>&, Result*, MatchType, unsigned int) [9]
[156]    0.0    0.00    0.00   16216         List<PayloadEntry>::getLen() const [156]
-----------------------------------------------
                0.00    0.00    2346/8936        List<Entry*>::List(List<Entry*> const&) [56]
                0.00    0.00    6590/8936        List<Entry*>::insert(Entry*&, Entry***) [153]
[157]    0.0    0.00    0.00    8936         ListNode<Entry*>::setNext(ListNode<Entry*>*) [157]
-----------------------------------------------
                0.00    0.00    4890/4890        findNextPrime(int) [161]
[158]    0.0    0.00    0.00    4890         isPrime(int) [158]
-----------------------------------------------
                0.00    0.00    4049/4049        List<PayloadEntry>::insert(PayloadEntry&, PayloadEntry**) [146]
[159]    0.0    0.00    0.00    4049         ListNode<PayloadEntry>::setNext(ListNode<PayloadEntry>*) [159]
-----------------------------------------------
                0.00    0.00       1/2933        CoreWrapper::~CoreWrapper() [61]
                0.00    0.00    1013/2933        CoreWrapper::deactivateQuery(unsigned int) [92]
                0.00    0.00    1919/2933        CoreWrapper::addQuery(unsigned int, char const*, MatchType, unsigned int) [20]
[160]    0.0    0.00    0.00    2933         Scheduler::waitPendingMatchesFinish() [160]
-----------------------------------------------
                0.00    0.00      10/2406        CoreWrapper::CoreWrapper() [237]
                0.00    0.00    2396/2406        scan(int, char const*, Word***, int*, int, int) [18]
[161]    0.0    0.00    0.00    2406         findNextPrime(int) [161]
                0.00    0.00    4890/4890        isPrime(int) [158]
-----------------------------------------------
                0.00    0.00       1/2389        EntryList::~EntryList() [106]
                0.00    0.00       9/2389        Index::~Index() [64]
                0.00    0.00    2379/2389        scan(int, char const*, Word***, int*, int, int) [18]
[162]    0.0    0.00    0.00    2389         HashTable::~HashTable() [162]
                0.00    0.00  450610/450610      Bucket::~Bucket() [134]
-----------------------------------------------
                0.00    0.00       1/2385        EntryList::EntryList(int) [255]
                0.00    0.00       9/2385        Index::Index(MatchType, int) [206]
                0.00    0.00    2375/2385        scan(int, char const*, Word***, int*, int, int) [18]
[163]    0.0    0.00    0.00    2385         HashTable::HashTable(int, unsigned long (*)(char const*)) [163]
                0.00    0.00  466087/466087      Bucket::Bucket() [131]
-----------------------------------------------
                0.00    0.00     441/2361        Document::Document(unsigned int, char const*) [53]
                0.00    0.00    1920/2361        Query::Query(unsigned int, char const*, MatchType, unsigned int) [21]
[164]    0.0    0.00    0.00    2361         countSpaces(char const*) [164]
-----------------------------------------------
                0.00    0.00    1920/1920        EntryList::insert(Query&, Entry***) [84]
[165]    0.0    0.00    0.00    1920         Query::getMatchDist() [165]
-----------------------------------------------
                0.00    0.00    1920/1920        EntryList::insert(Query&, Entry***) [84]
[166]    0.0    0.00    0.00    1920         Query::getAdressOfActive() [166]
-----------------------------------------------
                0.00    0.00    1920/1920        EntryList::insert(Query&, Entry***) [84]
[167]    0.0    0.00    0.00    1920         Query::getType() [167]
-----------------------------------------------
                0.00    0.00    1920/1920        Vector<Query*>::destroyData() [253]
[168]    0.0    0.00    0.00    1920         Query::~Query() [168]
                0.00    0.00    4158/424787      Word::~Word() [136]
-----------------------------------------------
                0.00    0.00      48/1628        List<Result*>::~List() [242]
                0.00    0.00     452/1628        List<Result*>::removeIdx(int) [191]
                0.00    0.00    1128/1628        List<Result*>::getItem(int) const [185]
[169]    0.0    0.00    0.00    1628         ListNode<Result*>::getNext() const [169]
-----------------------------------------------
                0.00    0.00     485/1334        Scheduler::doJob(Job*, int) [2]
                0.00    0.00     849/1334        Scheduler::waitForAvailRes() [195]
[170]    0.0    0.00    0.00    1334         Queue<Result*>::getList() [170]
-----------------------------------------------
                0.00    0.00     474/1312        Scheduler::doJob(Job*, int) [2]
                0.00    0.00     838/1312        Scheduler::waitForAvailRes() [195]
[171]    0.0    0.00    0.00    1312         List<Result*>::getLen() const [171]
-----------------------------------------------
                0.00    0.00       1/1281        giveJobFunction(void*) [7]
                0.00    0.00    1280/1281        doJobFunction(void*) [1]
[172]    0.0    0.00    0.00    1281         ArgClass::~ArgClass() [172]
-----------------------------------------------
                0.00    0.00    1271/1271        Scheduler::Scheduler(int) [256]
[173]    0.0    0.00    0.00    1271         ArgClass::ArgClass(int, Scheduler*) [173]
-----------------------------------------------
                0.00    0.00       1/1255        giveJobFunction(void*) [7]
                0.00    0.00    1254/1255        doJobFunction(void*) [1]
[174]    0.0    0.00    0.00    1255         ArgClass::getSched() [174]
-----------------------------------------------
                0.00    0.00    1253/1253        doJobFunction(void*) [1]
[175]    0.0    0.00    0.00    1253         ArgClass::getId() [175]
-----------------------------------------------
                0.00    0.00    1013/1013        CoreWrapper::deactivateQuery(unsigned int) [92]
[176]    0.0    0.00    0.00    1013         Query::deactivate() [176]
-----------------------------------------------
                0.00    0.00     550/550         Scheduler::doJob(Job*, int) [2]
[177]    0.0    0.00    0.00     550         CoreWrapper::addResult(Result*) [177]
                0.00    0.00     495/495         Queue<Result*>::push(Result*&) [184]
-----------------------------------------------
                0.00    0.00     521/521         Job::~Job() [37]
[178]    0.0    0.00    0.00     521         SearchArgs::~SearchArgs() [178]
                0.00    0.00     482/482         SearchArgs::~SearchArgs() [186]
-----------------------------------------------
                0.00    0.00      48/514         List<Result*>::~List() [242]
                0.00    0.00     466/514         List<Result*>::removeIdx(int) [191]
[179]    0.0    0.00    0.00     514         ListNode<Result*>::~ListNode() [179]
-----------------------------------------------
                0.00    0.00       1/509         CoreWrapper::~CoreWrapper() [61]
                0.00    0.00     508/509         Result::~Result() [98]
[180]    0.0    0.00    0.00     509         Vector<Query*>::~Vector() [180]
-----------------------------------------------
                0.00    0.00     507/507         List<Result*>::insert(Result*&, Result***) [187]
[181]    0.0    0.00    0.00     507         ListNode<Result*>::ListNode(Result*&) [181]
-----------------------------------------------
                0.00    0.00     503/503         List<Result*>::getItem(int) const [185]
[182]    0.0    0.00    0.00     503         ListNode<Result*>::getData() [182]
-----------------------------------------------
                0.00    0.00     503/503         CoreWrapper::pullResult() [196]
[183]    0.0    0.00    0.00     503         Scheduler::resMutexDown() [183]
-----------------------------------------------
                0.00    0.00     495/495         CoreWrapper::addResult(Result*) [177]
[184]    0.0    0.00    0.00     495         Queue<Result*>::push(Result*&) [184]
                0.00    0.00     481/481         List<Result*>::insert(Result*&, Result***) [187]
-----------------------------------------------
                0.00    0.00      48/495         List<Result*>::destroyData() [99]
                0.00    0.00     447/495         Queue<Result*>::pop() [192]
[185]    0.0    0.00    0.00     495         List<Result*>::getItem(int) const [185]
                0.00    0.00    1128/1628        ListNode<Result*>::getNext() const [169]
                0.00    0.00     503/503         ListNode<Result*>::getData() [182]
-----------------------------------------------
                0.00    0.00     482/482         SearchArgs::~SearchArgs() [178]
[186]    0.0    0.00    0.00     482         SearchArgs::~SearchArgs() [186]
                0.00    0.00     477/1675490     Args::~Args() [121]
-----------------------------------------------
                0.00    0.00     481/481         Queue<Result*>::push(Result*&) [184]
[187]    0.0    0.00    0.00     481         List<Result*>::insert(Result*&, Result***) [187]
                0.00    0.00     507/507         ListNode<Result*>::ListNode(Result*&) [181]
                0.00    0.00      69/69          ListNode<Result*>::setNext(ListNode<Result*>*) [201]
-----------------------------------------------
                0.00    0.00     461/461         Scheduler::doJob(Job*, int) [2]
[188]    0.0    0.00    0.00     461         SearchArgs::getDocument() [188]
-----------------------------------------------
                0.00    0.00     460/460         CoreWrapper::pullResult() [196]
[189]    0.0    0.00    0.00     460         Scheduler::resMutexUp() [189]
-----------------------------------------------
                0.00    0.00     454/454         Scheduler::doJob(Job*, int) [2]
[190]    0.0    0.00    0.00     454         Document::getWordsInDoc() [190]
-----------------------------------------------
                0.00    0.00     450/450         Queue<Result*>::pop() [192]
[191]    0.0    0.00    0.00     450         List<Result*>::removeIdx(int) [191]
                0.00    0.00     466/514         ListNode<Result*>::~ListNode() [179]
                0.00    0.00     452/1628        ListNode<Result*>::getNext() const [169]
-----------------------------------------------
                0.00    0.00     447/447         CoreWrapper::pullResult() [196]
[192]    0.0    0.00    0.00     447         Queue<Result*>::pop() [192]
                0.00    0.00     450/450         List<Result*>::removeIdx(int) [191]
                0.00    0.00     447/495         List<Result*>::getItem(int) const [185]
-----------------------------------------------
                0.00    0.00     435/435         Scheduler::doJob(Job*, int) [2]
[193]    0.0    0.00    0.00     435         Document::getId() [193]
-----------------------------------------------
                0.00    0.00     431/431         CoreWrapper::matchDocument(Document*) [96]
[194]    0.0    0.00    0.00     431         SearchArgs::SearchArgs(Document*) [194]
                0.00    0.00     435/1906623     Args::Args() [117]
-----------------------------------------------
                0.00    0.00     424/424         CoreWrapper::pullResult() [196]
[195]    0.0    0.00    0.00     424         Scheduler::waitForAvailRes() [195]
                0.00    0.00     849/1334        Queue<Result*>::getList() [170]
                0.00    0.00     838/1312        List<Result*>::getLen() const [171]
-----------------------------------------------
                0.00    0.00     399/399         GetNextAvailRes [82]
[196]    0.0    0.00    0.00     399         CoreWrapper::pullResult() [196]
                0.00    0.00     503/503         Scheduler::resMutexDown() [183]
                0.00    0.00     460/460         Scheduler::resMutexUp() [189]
                0.00    0.00     447/447         Queue<Result*>::pop() [192]
                0.00    0.00     424/424         Scheduler::waitForAvailRes() [195]
-----------------------------------------------
                0.00    0.00     112/112         Index::Index(MatchType, int) [206]
[197]    0.0    0.00    0.00     112         BKTree::BKTree(int (Word::*)(Word&)) [197]
-----------------------------------------------
                0.00    0.00      89/89          List<Entry>::insert(Entry&, Entry**) [101]
[198]    0.0    0.00    0.00      89         ListNode<Entry>::getData() [198]
-----------------------------------------------
                0.00    0.00      89/89          List<Entry>::~List() [105]
[199]    0.0    0.00    0.00      89         ListNode<Entry>::getNext() const [199]
-----------------------------------------------
                0.00    0.00      88/88          List<Entry>::insert(Entry&, Entry**) [101]
[200]    0.0    0.00    0.00      88         ListNode<Entry>::setNext(ListNode<Entry>*) [200]
-----------------------------------------------
                0.00    0.00      69/69          List<Result*>::insert(Result*&, Result***) [187]
[201]    0.0    0.00    0.00      69         ListNode<Result*>::setNext(ListNode<Result*>*) [201]
-----------------------------------------------
                0.00    0.00      67/67          BKTree::insert(BKNode**, Entry*, int) [95]
[202]    0.0    0.00    0.00      67         BKNode::BKNode(Entry*, int) [202]
                0.00    0.00      67/67          Vector<BKNode*>::Vector() [203]
-----------------------------------------------
                0.00    0.00      67/67          BKNode::BKNode(Entry*, int) [202]
[203]    0.0    0.00    0.00      67         Vector<BKNode*>::Vector() [203]
-----------------------------------------------
                0.00    0.00      67/67          BKNode::~BKNode() [77]
[204]    0.0    0.00    0.00      67         Vector<BKNode*>::~Vector() [204]
-----------------------------------------------
                0.00    0.00      48/48          BKTree::insert(BKNode**, Entry*, int) [95]
[205]    0.0    0.00    0.00      48         Vector<BKNode*>::insert(BKNode*&) [205]
-----------------------------------------------
                0.00    0.00       9/9           CoreWrapper::CoreWrapper() [237]
[206]    0.0    0.00    0.00       9         Index::Index(MatchType, int) [206]
                0.00    0.00     112/112         BKTree::BKTree(int (Word::*)(Word&)) [197]
                0.00    0.00       9/2385        HashTable::HashTable(int, unsigned long (*)(char const*)) [163]
-----------------------------------------------
                0.00    0.00       2/2           TestSigmod(char const*) [16]
[207]    0.0    0.00    0.00       2         GetClockTimeInMilliSec() [207]
-----------------------------------------------
                0.00    0.00       1/1           __libc_csu_init [50]
[208]    0.0    0.00    0.00       1         _GLOBAL__sub_I_CW [208]
                0.00    0.00       1/1           __static_initialization_and_destruction_0(int, int) [230]
-----------------------------------------------
                0.00    0.00       1/1           __libc_csu_init [50]
[209]    0.0    0.00    0.00       1         _GLOBAL__sub_I__Z7isPrimei [209]
                0.00    0.00       1/1           __static_initialization_and_destruction_0(int, int) [227]
-----------------------------------------------
                0.00    0.00       1/1           __libc_csu_init [50]
[210]    0.0    0.00    0.00       1         _GLOBAL__sub_I__ZN11CoreWrapperC2Ev [210]
                0.00    0.00       1/1           __static_initialization_and_destruction_0(int, int) [229]
-----------------------------------------------
                0.00    0.00       1/1           __libc_csu_init [50]
[211]    0.0    0.00    0.00       1         _GLOBAL__sub_I__ZN12PayloadEntryC2EjPb [211]
                0.00    0.00       1/1           __static_initialization_and_destruction_0(int, int) [231]
-----------------------------------------------
                0.00    0.00       1/1           __libc_csu_init [50]
[212]    0.0    0.00    0.00       1         _GLOBAL__sub_I__ZN4Args5printEv [212]
                0.00    0.00       1/1           __static_initialization_and_destruction_0(int, int) [235]
-----------------------------------------------
                0.00    0.00       1/1           __libc_csu_init [50]
[213]    0.0    0.00    0.00       1         _GLOBAL__sub_I__ZN5EntryC2EPKcR12PayloadEntry9MatchTypej [213]
                0.00    0.00       1/1           __static_initialization_and_destruction_0(int, int) [221]
-----------------------------------------------
                0.00    0.00       1/1           __libc_csu_init [50]
[214]    0.0    0.00    0.00       1         _GLOBAL__sub_I__ZN5IndexC2E9MatchTypei [214]
                0.00    0.00       1/1           __static_initialization_and_destruction_0(int, int) [226]
-----------------------------------------------
                0.00    0.00       1/1           __libc_csu_init [50]
[215]    0.0    0.00    0.00       1         _GLOBAL__sub_I__ZN5QueryC2EjPKc9MatchTypej [215]
                0.00    0.00       1/1           __static_initialization_and_destruction_0(int, int) [224]
-----------------------------------------------
                0.00    0.00       1/1           __libc_csu_init [50]
[216]    0.0    0.00    0.00       1         _GLOBAL__sub_I__ZN6BucketC2Ev [216]
                0.00    0.00       1/1           __static_initialization_and_destruction_0(int, int) [223]
-----------------------------------------------
                0.00    0.00       1/1           __libc_csu_init [50]
[217]    0.0    0.00    0.00       1         _GLOBAL__sub_I__ZN6ResultC2EjR6VectorIP5QueryE [217]
                0.00    0.00       1/1           __static_initialization_and_destruction_0(int, int) [233]
-----------------------------------------------
                0.00    0.00       1/1           __libc_csu_init [50]
[218]    0.0    0.00    0.00       1         _GLOBAL__sub_I__ZN8DocumentC2EjPKc [218]
                0.00    0.00       1/1           __static_initialization_and_destruction_0(int, int) [232]
-----------------------------------------------
                0.00    0.00       1/1           __libc_csu_init [50]
[219]    0.0    0.00    0.00       1         _GLOBAL__sub_I__ZN9EntryListC2Ei [219]
                0.00    0.00       1/1           __static_initialization_and_destruction_0(int, int) [228]
-----------------------------------------------
                0.00    0.00       1/1           __libc_csu_init [50]
[220]    0.0    0.00    0.00       1         _GLOBAL__sub_I__ZN9Scheduler24waitPendingMatchesFinishEv [220]
                0.00    0.00       1/1           __static_initialization_and_destruction_0(int, int) [234]
-----------------------------------------------
                0.00    0.00       1/1           _GLOBAL__sub_I__ZN5EntryC2EPKcR12PayloadEntry9MatchTypej [213]
[221]    0.0    0.00    0.00       1         __static_initialization_and_destruction_0(int, int) [221]
-----------------------------------------------
                0.00    0.00       1/1           _GLOBAL__sub_I__ZN4WordC2EPKc [58]
[222]    0.0    0.00    0.00       1         __static_initialization_and_destruction_0(int, int) [222]
-----------------------------------------------
                0.00    0.00       1/1           _GLOBAL__sub_I__ZN6BucketC2Ev [216]
[223]    0.0    0.00    0.00       1         __static_initialization_and_destruction_0(int, int) [223]
-----------------------------------------------
                0.00    0.00       1/1           _GLOBAL__sub_I__ZN5QueryC2EjPKc9MatchTypej [215]
[224]    0.0    0.00    0.00       1         __static_initialization_and_destruction_0(int, int) [224]
-----------------------------------------------
                0.00    0.00       1/1           _GLOBAL__sub_I__ZN6BKTreeC2EM4WordFiRS0_E [80]
[225]    0.0    0.00    0.00       1         __static_initialization_and_destruction_0(int, int) [225]
-----------------------------------------------
                0.00    0.00       1/1           _GLOBAL__sub_I__ZN5IndexC2E9MatchTypei [214]
[226]    0.0    0.00    0.00       1         __static_initialization_and_destruction_0(int, int) [226]
-----------------------------------------------
                0.00    0.00       1/1           _GLOBAL__sub_I__Z7isPrimei [209]
[227]    0.0    0.00    0.00       1         __static_initialization_and_destruction_0(int, int) [227]
-----------------------------------------------
                0.00    0.00       1/1           _GLOBAL__sub_I__ZN9EntryListC2Ei [219]
[228]    0.0    0.00    0.00       1         __static_initialization_and_destruction_0(int, int) [228]
-----------------------------------------------
                0.00    0.00       1/1           _GLOBAL__sub_I__ZN11CoreWrapperC2Ev [210]
[229]    0.0    0.00    0.00       1         __static_initialization_and_destruction_0(int, int) [229]
-----------------------------------------------
                0.00    0.00       1/1           _GLOBAL__sub_I_CW [208]
[230]    0.0    0.00    0.00       1         __static_initialization_and_destruction_0(int, int) [230]
-----------------------------------------------
                0.00    0.00       1/1           _GLOBAL__sub_I__ZN12PayloadEntryC2EjPb [211]
[231]    0.0    0.00    0.00       1         __static_initialization_and_destruction_0(int, int) [231]
-----------------------------------------------
                0.00    0.00       1/1           _GLOBAL__sub_I__ZN8DocumentC2EjPKc [218]
[232]    0.0    0.00    0.00       1         __static_initialization_and_destruction_0(int, int) [232]
-----------------------------------------------
                0.00    0.00       1/1           _GLOBAL__sub_I__ZN6ResultC2EjR6VectorIP5QueryE [217]
[233]    0.0    0.00    0.00       1         __static_initialization_and_destruction_0(int, int) [233]
-----------------------------------------------
                0.00    0.00       1/1           _GLOBAL__sub_I__ZN9Scheduler24waitPendingMatchesFinishEv [220]
[234]    0.0    0.00    0.00       1         __static_initialization_and_destruction_0(int, int) [234]
-----------------------------------------------
                0.00    0.00       1/1           _GLOBAL__sub_I__ZN4Args5printEv [212]
[235]    0.0    0.00    0.00       1         __static_initialization_and_destruction_0(int, int) [235]
-----------------------------------------------
                0.00    0.00       1/1           TestSigmod(char const*) [16]
[236]    0.0    0.00    0.00       1         PrintTime(int) [236]
-----------------------------------------------
                0.00    0.00       1/1           InitializeIndex [108]
[237]    0.0    0.00    0.00       1         CoreWrapper::CoreWrapper() [237]
                0.00    0.00      10/2406        findNextPrime(int) [161]
                0.00    0.00       9/9           Index::Index(MatchType, int) [206]
                0.00    0.00       1/1           Scheduler::Scheduler(int) [256]
                0.00    0.00       1/1           EntryList::EntryList(int) [255]
                0.00    0.00       1/1           Vector<Query*>::Vector() [254]
                0.00    0.00       1/1           Queue<Document*>::Queue() [251]
                0.00    0.00       1/1           Queue<Result*>::Queue() [248]
-----------------------------------------------
                0.00    0.00       1/1           EntryList::EntryList(int) [255]
[238]    0.0    0.00    0.00       1         List<Entry>::List() [238]
-----------------------------------------------
                0.00    0.00       1/1           Queue<Job*>::Queue() [246]
[239]    0.0    0.00    0.00       1         List<Job*>::List() [239]
-----------------------------------------------
                0.00    0.00       1/1           Queue<Job*>::~Queue() [247]
[240]    0.0    0.00    0.00       1         List<Job*>::~List() [240]
-----------------------------------------------
                0.00    0.00       1/1           Queue<Result*>::Queue() [248]
[241]    0.0    0.00    0.00       1         List<Result*>::List() [241]
-----------------------------------------------
                0.00    0.00       1/1           Queue<Result*>::~Queue() [249]
[242]    0.0    0.00    0.00       1         List<Result*>::~List() [242]
                0.00    0.00      48/1628        ListNode<Result*>::getNext() const [169]
                0.00    0.00      48/514         ListNode<Result*>::~ListNode() [179]
-----------------------------------------------
                0.00    0.00       1/1           Queue<Document*>::destroyData() [250]
[243]    0.0    0.00    0.00       1         List<Document*>::destroyData() [243]
-----------------------------------------------
                0.00    0.00       1/1           Queue<Document*>::Queue() [251]
[244]    0.0    0.00    0.00       1         List<Document*>::List() [244]
-----------------------------------------------
                0.00    0.00       1/1           Queue<Document*>::~Queue() [252]
[245]    0.0    0.00    0.00       1         List<Document*>::~List() [245]
-----------------------------------------------
                0.00    0.00       1/1           Scheduler::Scheduler(int) [256]
[246]    0.0    0.00    0.00       1         Queue<Job*>::Queue() [246]
                0.00    0.00       1/1           List<Job*>::List() [239]
-----------------------------------------------
                0.00    0.00       1/1           Scheduler::~Scheduler() [257]
[247]    0.0    0.00    0.00       1         Queue<Job*>::~Queue() [247]
                0.00    0.00       1/1           List<Job*>::~List() [240]
-----------------------------------------------
                0.00    0.00       1/1           CoreWrapper::CoreWrapper() [237]
[248]    0.0    0.00    0.00       1         Queue<Result*>::Queue() [248]
                0.00    0.00       1/1           List<Result*>::List() [241]
-----------------------------------------------
                0.00    0.00       1/1           CoreWrapper::~CoreWrapper() [61]
[249]    0.0    0.00    0.00       1         Queue<Result*>::~Queue() [249]
                0.00    0.00       1/1           List<Result*>::~List() [242]
-----------------------------------------------
                0.00    0.00       1/1           CoreWrapper::~CoreWrapper() [61]
[250]    0.0    0.00    0.00       1         Queue<Document*>::destroyData() [250]
                0.00    0.00       1/1           List<Document*>::destroyData() [243]
-----------------------------------------------
                0.00    0.00       1/1           CoreWrapper::CoreWrapper() [237]
[251]    0.0    0.00    0.00       1         Queue<Document*>::Queue() [251]
                0.00    0.00       1/1           List<Document*>::List() [244]
-----------------------------------------------
                0.00    0.00       1/1           CoreWrapper::~CoreWrapper() [61]
[252]    0.0    0.00    0.00       1         Queue<Document*>::~Queue() [252]
                0.00    0.00       1/1           List<Document*>::~List() [245]
-----------------------------------------------
                0.00    0.00       1/1           CoreWrapper::~CoreWrapper() [61]
[253]    0.0    0.00    0.00       1         Vector<Query*>::destroyData() [253]
                0.00    0.00    1920/1920        Query::~Query() [168]
-----------------------------------------------
                0.00    0.00       1/1           CoreWrapper::CoreWrapper() [237]
[254]    0.0    0.00    0.00       1         Vector<Query*>::Vector() [254]
-----------------------------------------------
                0.00    0.00       1/1           CoreWrapper::CoreWrapper() [237]
[255]    0.0    0.00    0.00       1         EntryList::EntryList(int) [255]
                0.00    0.00       1/2385        HashTable::HashTable(int, unsigned long (*)(char const*)) [163]
                0.00    0.00       1/1           List<Entry>::List() [238]
-----------------------------------------------
                0.00    0.00       1/1           CoreWrapper::CoreWrapper() [237]
[256]    0.0    0.00    0.00       1         Scheduler::Scheduler(int) [256]
                0.00    0.00    1271/1271        ArgClass::ArgClass(int, Scheduler*) [173]
                0.00    0.00       1/1           Queue<Job*>::Queue() [246]
-----------------------------------------------
                0.00    0.00       1/1           CoreWrapper::~CoreWrapper() [61]
[257]    0.0    0.00    0.00       1         Scheduler::~Scheduler() [257]
                0.00    0.00       1/1           Queue<Job*>::~Queue() [247]
-----------------------------------------------

 This table describes the call tree of the program, and was sorted by
 the total amount of time spent in each function and its children.

 Each entry in this table consists of several lines.  The line with the
 index number at the left hand margin lists the current function.
 The lines above it list the functions that called this function,
 and the lines below it list the functions this one called.
 This line lists:
     index	A unique number given to each element of the table.
		Index numbers are sorted numerically.
		The index number is printed next to every function name so
		it is easier to look up where the function is in the table.

     % time	This is the percentage of the `total' time that was spent
		in this function and its children.  Note that due to
		different viewpoints, functions excluded by options, etc,
		these numbers will NOT add up to 100%.

     self	This is the total amount of time spent in this function.

     children	This is the total amount of time propagated into this
		function by its children.

     called	This is the number of times the function was called.
		If the function called itself recursively, the number
		only includes non-recursive calls, and is followed by
		a `+' and the number of recursive calls.

     name	The name of the current function.  The index number is
		printed after it.  If the function is a member of a
		cycle, the cycle number is printed between the
		function's name and the index number.


 For the function's parents, the fields have the following meanings:

     self	This is the amount of time that was propagated directly
		from the function into this parent.

     children	This is the amount of time that was propagated from
		the function's children into this parent.

     called	This is the number of times this parent called the
		function `/' the total number of times the function
		was called.  Recursive calls to the function are not
		included in the number after the `/'.

     name	This is the name of the parent.  The parent's index
		number is printed after it.  If the parent is a
		member of a cycle, the cycle number is printed between
		the name and the index number.

 If the parents of the function cannot be determined, the word
 `<spontaneous>' is printed in the `name' field, and all the other
 fields are blank.

 For the function's children, the fields have the following meanings:

     self	This is the amount of time that was propagated directly
		from the child into the function.

     children	This is the amount of time that was propagated from the
		child's children to the function.

     called	This is the number of times the function called
		this child `/' the total number of times the child
		was called.  Recursive calls by the child are not
		listed in the number after the `/'.

     name	This is the name of the child.  The child's index
		number is printed after it.  If the child is a
		member of a cycle, the cycle number is printed
		between the name and the index number.

 If there are any cycles (circles) in the call graph, there is an
 entry for the cycle-as-a-whole.  This entry shows who called the
 cycle (as parents) and the members of the cycle (as children.)
 The `+' recursive calls entry shows the number of function calls that
 were internal to the cycle, and the calls entry for each member shows,
 for that member, how many times it was called from other members of
 the cycle.

Copyright (C) 2012-2020 Free Software Foundation, Inc.

Copying and distribution of this file, with or without modification,
are permitted in any medium without royalty provided the copyright
notice and this notice are preserved.

Index by function name

  [60] DestroyIndex          [107] List<PayloadEntry>::List(List<PayloadEntry> const&) [11] Result::increaseCounter(unsigned int, Word*)
  [90] EndQuery              [115] List<PayloadEntry>::List() [83] Result::fetch(unsigned int*, unsigned int*, unsigned int**)
  [82] GetNextAvailRes        [87] List<PayloadEntry>::~List() [28] Result::Result(unsigned int, Vector<Query*>&)
 [108] InitializeIndex       [101] List<Entry>::insert(Entry&, Entry**) [98] Result::~Result()
  [52] MatchDocument         [238] List<Entry>::List()    [75] Vector<Entry*>::insert(Entry*&)
  [19] StartQuery            [105] List<Entry>::~List()  [130] Vector<Entry*>::Vector()
 [208] _GLOBAL__sub_I_CW (core.cpp) [44] List<Job*>::insert(Job*&, Job***) [133] Vector<Entry*>::~Vector()
 [209] _GLOBAL__sub_I__Z7isPrimei (utils.cpp) [30] List<Job*>::removeIdx(int) [253] Vector<Query*>::destroyData()
 [210] _GLOBAL__sub_I__ZN11CoreWrapperC2Ev (core_wrapper.cpp) [239] List<Job*>::List() [97] Vector<Query*>::insertSorted(Query*&, int)
 [211] _GLOBAL__sub_I__ZN12PayloadEntryC2EjPb (payload_entry.cpp) [240] List<Job*>::~List() [254] Vector<Query*>::Vector()
 [212] _GLOBAL__sub_I__ZN4Args5printEv (job.cpp) [33] List<Entry*>::append(List<Entry*>*) [76] Vector<Query*>::Vector(Vector<Query*> const&)
  [58] _GLOBAL__sub_I__ZN4WordC2EPKc (word.cpp) [153] List<Entry*>::insert(Entry*&, Entry***) [180] Vector<Query*>::~Vector()
 [213] _GLOBAL__sub_I__ZN5EntryC2EPKcR12PayloadEntry9MatchTypej (entry.cpp) [56] List<Entry*>::List(List<Entry*> const&) [205] Vector<BKNode*>::insert(BKNode*&)
 [214] _GLOBAL__sub_I__ZN5IndexC2E9MatchTypei (index.cpp) [35] List<Entry*>::List() [203] Vector<BKNode*>::Vector()
 [215] _GLOBAL__sub_I__ZN5QueryC2EjPKc9MatchTypej (query.cpp) [40] List<Entry*>::~List() [204] Vector<BKNode*>::~Vector()
  [80] _GLOBAL__sub_I__ZN6BKTreeC2EM4WordFiRS0_E (BK_tree.cpp) [99] List<Result*>::destroyData() [175] ArgClass::getId()
 [216] _GLOBAL__sub_I__ZN6BucketC2Ev (hash_table.cpp) [187] List<Result*>::insert(Result*&, Result***) [174] ArgClass::getSched()
 [217] _GLOBAL__sub_I__ZN6ResultC2EjR6VectorIP5QueryE (result.cpp) [191] List<Result*>::removeIdx(int) [173] ArgClass::ArgClass(int, Scheduler*)
 [218] _GLOBAL__sub_I__ZN8DocumentC2EjPKc (document.cpp) [241] List<Result*>::List() [172] ArgClass::~ArgClass()
 [219] _GLOBAL__sub_I__ZN9EntryListC2Ei (entry_list.cpp) [242] List<Result*>::~List() [190] Document::getWordsInDoc()
 [220] _GLOBAL__sub_I__ZN9Scheduler24waitPendingMatchesFinishEv (scheduler.cpp) [243] List<Document*>::destroyData() [193] Document::getId()
  [16] TestSigmod(char const*) [244] List<Document*>::List() [140] Document::getWord(int)
 [164] countSpaces(char const*) [245] List<Document*>::~List() [53] Document::Document(unsigned int, char const*)
  [91] biSearchQuery(Vector<Query*>*, unsigned int) [24] Word::exactMatch(Word&) [132] ListNode<PayloadEntry>::getData()
   [1] doJobFunction(void*)   [25] Word::hammingDist(Word&) [159] ListNode<PayloadEntry>::setNext(ListNode<PayloadEntry>*)
 [161] findNextPrime(int)     [27] Word::getLen()        [142] ListNode<PayloadEntry>::ListNode(PayloadEntry&)
  [36] checkCondition(pthread_mutex_t*, pthread_mutex_t*, bool*) [120] Word::getStr() [141] ListNode<PayloadEntry>::~ListNode()
   [7] giveJobFunction(void*)  [6] Word::editDist(Word&) [198] ListNode<Entry>::getData()
  [14] biSearchQueryIndex(Vector<Query*>*, unsigned int) [135] Word::Word(char const*) [200] ListNode<Entry>::setNext(ListNode<Entry>*)
 [207] GetClockTimeInMilliSec() [148] Word::Word(Word&)  [103] ListNode<Entry>::ListNode(Entry&)
 [221] __static_initialization_and_destruction_0(int, int) (entry.cpp) [136] Word::~Word() [104] ListNode<Entry>::~ListNode()
 [222] __static_initialization_and_destruction_0(int, int) (word.cpp) [155] Entry::getPayload(MatchType, unsigned int) [124] ListNode<Job*>::getData()
 [223] __static_initialization_and_destruction_0(int, int) (hash_table.cpp) [144] Entry::addToPayload(PayloadEntry&, MatchType, unsigned int) [116] ListNode<Job*>::setNext(ListNode<Job*>*)
 [224] __static_initialization_and_destruction_0(int, int) (query.cpp) [66] Entry::getWord() [67] ListNode<Job*>::ListNode(Job*&)
 [225] __static_initialization_and_destruction_0(int, int) (BK_tree.cpp) [102] Entry::Entry(Entry&) [47] ListNode<Job*>::~ListNode()
 [226] __static_initialization_and_destruction_0(int, int) (index.cpp) [147] Entry::Entry(Word&, PayloadEntry&, MatchType, unsigned int) [151] ListNode<Entry*>::getData()
 [227] __static_initialization_and_destruction_0(int, int) (utils.cpp) [88] Entry::~Entry() [157] ListNode<Entry*>::setNext(ListNode<Entry*>*)
 [228] __static_initialization_and_destruction_0(int, int) (entry_list.cpp) [93] Index::insert(Entry*) [152] ListNode<Entry*>::ListNode(Entry*&)
 [229] __static_initialization_and_destruction_0(int, int) (core_wrapper.cpp) [86] Index::insert(Entry**) [150] ListNode<Entry*>::~ListNode()
 [230] __static_initialization_and_destruction_0(int, int) (core.cpp) [3] Index::search(Word*, int) [182] ListNode<Result*>::getData()
 [231] __static_initialization_and_destruction_0(int, int) (payload_entry.cpp) [206] Index::Index(MatchType, int) [201] ListNode<Result*>::setNext(ListNode<Result*>*)
 [232] __static_initialization_and_destruction_0(int, int) (document.cpp) [64] Index::~Index() [181] ListNode<Result*>::ListNode(Result*&)
 [233] __static_initialization_and_destruction_0(int, int) (result.cpp) [176] Query::deactivate() [179] ListNode<Result*>::~ListNode()
 [234] __static_initialization_and_destruction_0(int, int) (scheduler.cpp) [165] Query::getMatchDist() [85] EntryList::insert(Word*, PayloadEntry&, MatchType, unsigned int, Entry**)
 [235] __static_initialization_and_destruction_0(int, int) (job.cpp) [128] Query::getWordsInQuery() [84] EntryList::insert(Query&, Entry***)
  [31] djb2(char const*)     [166] Query::getAdressOfActive() [255] EntryList::EntryList(int)
  [18] scan(int, char const*, Word***, int*, int, int) [34] Query::getId() [106] EntryList::~EntryList()
 [158] isPrime(int)          [167] Query::getType()       [42] HashTable::deleteData()
 [139] satisfy(bool*, int)    [38] Query::getWord(int)    [89] HashTable::updateEntryPayload(Word*, PayloadEntry&, MatchType, unsigned int)
 [236] PrintTime(int)         [21] Query::Query(unsigned int, char const*, MatchType, unsigned int) [41] HashTable::insert(Entry*)
 [188] SearchArgs::getDocument() [168] Query::~Query()    [22] HashTable::getEntry(Word*)
 [194] SearchArgs::SearchArgs(Document*) [12] Queue<Job*>::pop() [163] HashTable::HashTable(int, unsigned long (*)(char const*))
 [178] SearchArgs::~SearchArgs() [45] Queue<Job*>::push(Job*&) [162] HashTable::~HashTable()
 [186] SearchArgs::~SearchArgs() [123] Queue<Job*>::getList() [189] Scheduler::resMutexUp()
 [196] CoreWrapper::pullResult() [246] Queue<Job*>::Queue() [183] Scheduler::resMutexDown()
  [96] CoreWrapper::matchDocument(Document*) [247] Queue<Job*>::~Queue() [195] Scheduler::waitForAvailRes()
  [92] CoreWrapper::deactivateQuery(unsigned int) [100] Queue<Result*>::destroyData() [160] Scheduler::waitPendingMatchesFinish()
   [9] CoreWrapper::increaseCounter(List<Entry*>&, Result*, MatchType, unsigned int) [192] Queue<Result*>::pop() [2] Scheduler::doJob(Job*, int)
  [13] CoreWrapper::searchWordInIndeces(Word*, Result*, int) [184] Queue<Result*>::push(Result*&) [23] Scheduler::addJob(Job*)
  [20] CoreWrapper::addQuery(unsigned int, char const*, MatchType, unsigned int) [170] Queue<Result*>::getList() [8] Scheduler::assignJob()
 [177] CoreWrapper::addResult(Result*) [248] Queue<Result*>::Queue() [256] Scheduler::Scheduler(int)
 [237] CoreWrapper::CoreWrapper() [249] Queue<Result*>::~Queue() [257] Scheduler::~Scheduler()
  [61] CoreWrapper::~CoreWrapper() [250] Queue<Document*>::destroyData() [156] List<PayloadEntry>::getLen() const
 [138] PayloadEntry::getId() [251] Queue<Document*>::Queue() [17] List<PayloadEntry>::getItem(int) const
  [32] PayloadEntry::getActive() [252] Queue<Document*>::~Queue() [125] List<Job*>::getLen() const
 [143] PayloadEntry::PayloadEntry(PayloadEntry&) [72] BKNode::getChildren() [71] List<Job*>::getItem(int) const
 [145] PayloadEntry::PayloadEntry(unsigned int, bool*) [126] BKNode::getData() [65] List<Entry*>::getLen() const
 [137] PayloadEntry::~PayloadEntry() [127] BKNode::getDist() [154] List<Entry*>::getItem(int) const
  [79] SearchMethodArgs::getParentIndex() [202] BKNode::BKNode(Entry*, int) [171] List<Result*>::getLen() const
 [118] SearchMethodArgs::getRes() [77] BKNode::~BKNode() [185] List<Result*>::getItem(int) const
  [78] SearchMethodArgs::getDist() [94] BKTree::insert(Entry*) [49] Vector<Entry*>::getLen() const
  [54] SearchMethodArgs::getType() [95] BKTree::insert(BKNode**, Entry*, int) [129] Vector<Entry*>::getItem(int) const
  [55] SearchMethodArgs::getWord() [4] BKTree::search(Word*, int) [73] Vector<Query*>::getLen() const
  [46] SearchMethodArgs::SearchMethodArgs(Result*, Word*, int, int, int) [5] BKTree::search(BKNode*, Word*, int) [43] Vector<Query*>::getItem(int) const
  [70] SearchMethodArgs::~SearchMethodArgs() [62] BKTree::destroy(BKNode*) [57] Vector<BKNode*>::getLen() const
  [69] SearchMethodArgs::~SearchMethodArgs() [197] BKTree::BKTree(int (Word::*)(Word&)) [48] Vector<BKNode*>::getItem(int) const
  [26] Job::getId()           [63] BKTree::~BKTree()      [29] ListNode<PayloadEntry>::getNext() const
 [119] Job::getArgs()         [51] Bucket::bucketSize()  [199] ListNode<Entry>::getNext() const
  [68] Job::Job(JobId, Args*) [74] Bucket::insert(Entry*) [122] ListNode<Job*>::getNext() const
  [37] Job::~Job()            [39] Bucket::getEntry(Word*) [149] ListNode<Entry*>::getNext() const
 [117] Args::Args()           [81] Bucket::getEntry(int) [169] ListNode<Result*>::getNext() const
 [121] Args::~Args()         [131] Bucket::Bucket()       [10] int const& std::min<int>(int const&, int const&)
 [146] List<PayloadEntry>::insert(PayloadEntry&, PayloadEntry**) [134] Bucket::~Bucket() [59] operator<<(std::ostream&, Word const&)
