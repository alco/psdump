#ifndef PSDUMP_RECORD_H
#define PSDUMP_RECORD_H


/*
Abstract base class for subclasses which represent concrete layer
records and groups of layers.
*/
class Record {
 public:
  Record();
  Record(const char *name);
  virtual ~Record();

  const char * name() const { return name_; }
  void set_name(const char *);

  virtual bool is_group() const = 0;

 protected:
  char *name_;
};


#endif // PSDUMP_RECORD_H
