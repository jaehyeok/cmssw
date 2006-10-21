// -*- C++ -*-
//
// Package:    Framework
// Class:      TestESDummyDataAnalyzer
// 
/**\class TestESDummyDataAnalyzer TestESDummyDataAnalyzer.cc FWCore/Framework/test/stubs/TestESDummyDataAnalyzer.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Chris Jones
//         Created:  Thu Dec 22 11:02:00 EST 2005
// $Id: TestESDummyDataAnalyzer.cc,v 1.3 2006/09/01 18:16:43 wmtan Exp $
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/test/DummyData.h"

#include "FWCore/Utilities/interface/Exception.h"

//
// class decleration
//

class TestESDummyDataAnalyzer : public edm::EDAnalyzer {
   public:
      explicit TestESDummyDataAnalyzer(const edm::ParameterSet&);
      ~TestESDummyDataAnalyzer();


      virtual void analyze(const edm::Event&, const edm::EventSetup&);
   private:
         int m_expectedValue;
         int m_nEventsValue;
         int m_counter;
      // ----------member data ---------------------------
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
TestESDummyDataAnalyzer::TestESDummyDataAnalyzer(const edm::ParameterSet& iConfig) :
m_expectedValue(iConfig.getParameter<int>("expected")),
m_nEventsValue(iConfig.getUntrackedParameter<int>("nEvents",0)),
m_counter(0)
{
   //now do what ever initialization is needed

}


TestESDummyDataAnalyzer::~TestESDummyDataAnalyzer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
TestESDummyDataAnalyzer::analyze(const edm::Event&, const edm::EventSetup& iSetup)
{
   using namespace edm;

//   std::cout<<"before "<<m_expectedValue<<std::endl;
   if(m_nEventsValue) {
      ++m_counter;
      if(m_nEventsValue<m_counter) {
         ++m_expectedValue;
         m_counter=0;
      }
   }
   
   ESHandle<edm::eventsetup::test::DummyData> pData;
   iSetup.getData(pData);
//   std::cout<<"after "<<m_expectedValue<<" pData "<<pData->value_<<std::endl;

   if(m_expectedValue != pData->value_) {
      throw cms::Exception("WrongValue")<<"got value "<<pData->value_<<" but expected "<<m_expectedValue;
   }
   
}

//define this as a plug-in
DEFINE_FWK_MODULE(TestESDummyDataAnalyzer);
