/* Copyright 2013 The Blindsight Corporation */

#include <Python.h>
#include <structmember.h>
#include <tesseract/baseapi.h>
#include <numpy/arrayobject.h>
#include <iostream>

#pragma GCC diagnostic ignored "-Wwrite-strings"

// BoundingBox
typedef struct {
	PyObject_HEAD
	int left;
	int right;
	int top;
	int bottom;
} PyBoundingBox;

extern "C" {
	static int PyBoundingBox_init(PyBoundingBox *self, PyObject *args, PyObject *kwargs);
}

static PyMemberDef PyBoundingBox_members[] = {
	{ "left", T_INT, offsetof(PyBoundingBox, left), 0, PyDoc_STR("Left edge of the bounding box") },
	{ "right", T_INT, offsetof(PyBoundingBox, right), 0, PyDoc_STR("Right edge of the bounding box") },
	{ "top", T_INT, offsetof(PyBoundingBox, top), 0, PyDoc_STR("Top edge of the bounding box") },
	{ "bottom", T_INT, offsetof(PyBoundingBox, bottom), 0, PyDoc_STR("Bottom edge of the bounding box") },
	{ NULL }, // sentinel
};

static PyTypeObject PyBoundingBox_Type = {
	PyVarObject_HEAD_INIT(NULL, 0)
	"tesserpy.BoundingBox", // tp_name
	sizeof(PyBoundingBox), // tp_basicsize
	0, // tp_itemsize
	// methods
	0, // tp_dealloc
	0, // tp_print
	0, // tp_getattr
	0, // tp_setattr
	0, // tp_compare
	0, // tp_repr
	0, // tp_as_number
	0, // tp_as_sequence
	0, // tp_as_mapping
	0, // tp_hash
	0, // tp_call
	0, // tp_str
	0, // tp_getattro
	0, // tp_setattro
	0, // tp_as_buffer
	Py_TPFLAGS_DEFAULT, // tp_flags
	PyDoc_STR("A bounding box for a character, word, or line"), // tp_doc
	0, // tp_traverse
	0, // tp_clear
	0, // tp_richcompare
	0, // tp_weaklistoffset
	0, // tp_iter
	0, // tp_iternext
	0, // tp_methods
	PyBoundingBox_members, // tp_members
	0, // tp_getset
	0, // tp_base
	0, // tp_dict
	0, // tp_descr_get
	0, // tp_descr_set
	0, // tp_dictoffset
	(initproc)PyBoundingBox_init, // tp_init
	0, // tp_alloc
	0, // tp_new
	0, // tp_free
	0, // tp_is_gc
};

#define PyBoundingBox_Check(v) (Py_TYPE(v) == &PyBoundingBox_Type)

// Result
typedef struct {
	PyObject_HEAD
	PyObject *text;
	PyObject *bounding_box;
	float confidence;
} PyResult;

extern "C" {
	static int PyResult_init(PyResult *self, PyObject *args, PyObject *kwargs);
}

static PyMemberDef PyResult_members[] = {
	{ (char *)"text", T_OBJECT_EX, offsetof(PyResult, text), 0, PyDoc_STR("The detected text") },
	{ (char *)"bounding_box", T_OBJECT_EX, offsetof(PyResult, bounding_box), 0, PyDoc_STR("The detection's bounding box") },
	{ (char *)"confidence", T_FLOAT, offsetof(PyResult, confidence), 0, PyDoc_STR("Tesseract's confidence for the detection") },
	{ NULL }, // sentinel
};

static PyTypeObject PyResult_Type = {
	PyVarObject_HEAD_INIT(NULL, 0)
	"tesserpy.Result", // tp_name
	sizeof(PyResult), // tp_basicsize
	0, // tp_itemsize
	// methods
	0, // tp_dealloc
	0, // tp_print
	0, // tp_getattr
	0, // tp_setattr
	0, // tp_compare
	0, // tp_repr
	0, // tp_as_number
	0, // tp_as_sequence
	0, // tp_as_mapping
	0, // tp_hash
	0, // tp_call
	0, // tp_str
	0, // tp_getattro
	0, // tp_setattro
	0, // tp_as_buffer
	Py_TPFLAGS_DEFAULT, // tp_flags
	PyDoc_STR("A single Tesseract detection"), // tp_doc
	0, // tp_traverse
	0, // tp_clear
	0, // tp_richcompare
	0, // tp_weaklistoffset
	0, // tp_iter
	0, // tp_iternext
	0, // tp_methods
	PyResult_members, // tp_members
	0, // tp_getset
	0, // tp_base
	0, // tp_dict
	0, // tp_descr_get
	0, // tp_descr_set
	0, // tp_dictoffset
	(initproc)PyResult_init, // tp_init
	0, // tp_alloc
	0, // tp_new
	0, // tp_free
	0, // tp_is_gc
};

#define PyResult_Check(v) (Py_TYPE(v) == &PyResult_Type)

// ResultIterator
typedef struct {
	PyObject_HEAD
	tesseract::ResultIterator *ri;
	tesseract::PageIteratorLevel level;
	bool first;
} PyResultIterator;

extern "C" {
	static PyResultIterator* PyResultIterator_new(PyTypeObject *type, PyObject *args, PyObject *kwargs);
	static PyResultIterator* PyResultIterator_iter(PyResultIterator *self);
	static PyResult* PyResultIterator_next(PyResultIterator *self);
	static void PyResultIterator_dealloc(PyResultIterator *self);
}

static PyTypeObject PyResultIterator_Type = {
	PyVarObject_HEAD_INIT(NULL, 0)
	"tesserpy.ResultIterator", // tp_name
	sizeof(PyResultIterator), // tp_basicsize
	0, // tp_itemsize
	// methods
	(destructor)PyResultIterator_dealloc, // tp_dealloc
	0, // tp_print
	0, // tp_getattr
	0, // tp_setattr
	0, // tp_compare
	0, // tp_repr
	0, // tp_as_number
	0, // tp_as_sequence
	0, // tp_as_mapping
	0, // tp_hash
	0, // tp_call
	0, // tp_str
	0, // tp_getattro
	0, // tp_setattro
	0, // tp_as_buffer
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_ITER, // tp_flags
	PyDoc_STR("A single instance of a Tesseract ResultIterator object"), // tp_doc
	0, // tp_traverse
	0, // tp_clear
	0, // tp_richcompare
	0, // tp_weaklistoffset
	(getiterfunc)PyResultIterator_iter, // tp_iter
	(iternextfunc)PyResultIterator_next, // tp_iternext
	0, // tp_methods
	0, // tp_members
	0, // tp_getset
	0, // tp_base
	0, // tp_dict
	0, // tp_descr_get
	0, // tp_descr_set
	0, // tp_dictoffset
	0, // tp_init
	0, // tp_alloc
	(newfunc)PyResultIterator_new, // tp_new
	0, // tp_free
	0, // tp_is_gc
};

#define PyResultIterator_Check(v) (Py_TYPE(v) == &PyResultIterator_Type)

typedef struct {
	PyObject_HEAD
	tesseract::TessBaseAPI *tess;
	PyObject *image;
} PyTesseract;

extern "C" {
	static PyTesseract* PyTesseract_new(PyTypeObject *type, PyObject *args, PyObject *kwargs);
	static int PyTesseract_init(PyTesseract *self, PyObject *args, PyObject *kwargs);
	static PyObject* PyTesseract_clear(PyTesseract *self);
	static int PyTesseract_setattr(PyTesseract *self, PyObject *attr, PyObject *value);
	static PyObject* PyTesseract_getattr(PyTesseract *self, PyObject *attr);
	static PyObject* PyTesseract_set_image(PyTesseract *self, PyObject *args);
	static PyObject* PyTesseract_set_rectangle(PyTesseract *self, PyObject *args, PyObject *kwargs);
	static PyObject* PyTesseract_recognize(PyTesseract *self);
	static PyObject* PyTesseract_get_utf8_text(PyTesseract *self);
	static PyObject* PyTesseract_mean_text_conf(PyTesseract *self);
	static PyResultIterator* PyTesseract_symbols(PyTesseract *self);
	static PyResultIterator* PyTesseract_words(PyTesseract *self);
	static PyResultIterator* PyTesseract_text_lines(PyTesseract *self);
	static PyResultIterator* PyTesseract_paragraphs(PyTesseract *self);
	static PyResultIterator* PyTesseract_blocks(PyTesseract *self);
	static void PyTesseract_dealloc(PyTesseract *self);
}

static PyMethodDef PyTesseract_methods[] = {
	{ "clear", (PyCFunction)PyTesseract_clear, METH_NOARGS, PyDoc_STR("clear()\n\nFrees up recognition results and any stored image data") },
	{ "set_image", (PyCFunction)PyTesseract_set_image, METH_O, PyDoc_STR("set_image(image)\n\nProvides an image for Tesseract to recognize") },
	{ "set_rectangle", (PyCFunction)PyTesseract_set_rectangle, METH_KEYWORDS, PyDoc_STR("set_rectangle(left, top, width, height)\n\nRestricts recognition to a sub-rectangle of the image.") },
	{ "recognize", (PyCFunction)PyTesseract_recognize, METH_NOARGS, PyDoc_STR("recognize()\n\nTells Tesseract to run OCR. This method usually gets called by anything dependent on OCR having run already; it's only included here so the user can run it earlier.") },
	{ "get_utf8_text", (PyCFunction)PyTesseract_get_utf8_text, METH_NOARGS, PyDoc_STR("get_utf8_text()\n\nReturns recognized text.") },
	{ "mean_text_conf", (PyCFunction)PyTesseract_mean_text_conf, METH_NOARGS, PyDoc_STR("mean_text_conf()\n\nReturns the average word confidence value, between 0 and 100, for the Tesseract page result") },
	{ "symbols", (PyCFunction)PyTesseract_symbols, METH_NOARGS, PyDoc_STR("symbols()\n\nReturns an iterator over all detected characters in the document") },
	{ "words", (PyCFunction)PyTesseract_words, METH_NOARGS, PyDoc_STR("words()\n\nReturns an iterator over all detected words in the document") },
	{ "text_lines", (PyCFunction)PyTesseract_text_lines, METH_NOARGS, PyDoc_STR("text_lines()\n\nReturns an iterator over all detected lines of text in the document") },
	{ "paragraphs", (PyCFunction)PyTesseract_paragraphs, METH_NOARGS, PyDoc_STR("paragraphs()\n\nReturns an iterator over all detected paragraphs in the document") },
	{ "blocks", (PyCFunction)PyTesseract_blocks, METH_NOARGS, PyDoc_STR("blocks()\n\nReturns an iterator over all detected blocks of text in the document") },
	{ NULL, NULL } // sentinel
};

static PyTypeObject PyTesseract_Type = {
	PyVarObject_HEAD_INIT(NULL, 0)
	"tesserpy.Tesseract", // tp_name
	sizeof(PyTesseract), // tp_basicsize
	0, // tp_itemsize
	// methods
	(destructor)PyTesseract_dealloc, // tp_dealloc
	0, // tp_print
	0, // tp_getattr
	0, // tp_setattr
	0, // tp_compare
	0, // tp_repr
	0, // tp_as_number
	0, // tp_as_sequence
	0, // tp_as_mapping
	0, // tp_hash
	0, // tp_call
	0, // tp_str
	(getattrofunc)PyTesseract_getattr, // tp_getattro
	(setattrofunc)PyTesseract_setattr, // tp_setattro
	0, // tp_as_buffer
	Py_TPFLAGS_DEFAULT, // tp_flags
	PyDoc_STR("A single instance of a TessBaseAPI object"), // tp_doc
	0, // tp_traverse
	0, // tp_clear
	0, // tp_richcompare
	0, // tp_weaklistoffset
	0, // tp_iter
	0, // tp_iternext
	PyTesseract_methods, // tp_methods
	0, // tp_members
	0, // tp_getset
	0, // tp_base
	0, // tp_dict
	0, // tp_descr_get
	0, // tp_descr_set
	0, // tp_dictoffset
	(initproc)PyTesseract_init, // tp_init
	0, // tp_alloc
	(newfunc)PyTesseract_new, // tp_new
	0, // tp_free
	0, // tp_is_gc
};

#define PyTesseract_Check(v) (Py_TYPE(v) == &PyTesseract_Type)

/* BoundingBox methods */
	static int PyBoundingBox_init(PyBoundingBox *self, PyObject *args, PyObject *kwargs) {
		static const char *kwlist[] = { "left", "right", "top", "bottom", NULL };
		if (!PyArg_ParseTupleAndKeywords(args, kwargs, "iiii", (char **)kwlist, &self->left, &self->right, &self->top, &self->bottom)) {
			return -1;
		}
		return 0;
	}

/* Result methods */
	static int PyResult_init(PyResult *self, PyObject *args, PyObject *kwargs) {
		PyObject *text = NULL;
		PyObject *bounding_box = NULL;
		PyObject *temp = NULL;
		static const char *kwlist[] = { "text", "bounding_box", "confidence", NULL };
		if (!PyArg_ParseTupleAndKeywords(args, kwargs, "OOf", (char **)kwlist, &text, &bounding_box, &self->confidence)) {
			return -1;
		}

		if (text) {
			temp = self->text;
			Py_INCREF(text);
			self->text = text;
			Py_CLEAR(temp);
		}

		if (bounding_box) {
			temp = self->bounding_box;
			Py_INCREF(bounding_box);
			self->bounding_box = bounding_box;
			Py_CLEAR(bounding_box);
		}
		return 0;
	}

/* ResultIterator methods */

static PyResultIterator* PyResultIterator_new(PyTypeObject *type, PyObject* /* args */, PyObject* /* kwargs */) {
	PyResultIterator *self = PyObject_New(PyResultIterator, &PyResultIterator_Type);
	if (self == NULL) {
		return NULL;
	}
	self->ri = NULL;
	self->level = tesseract::RIL_BLOCK;
	self->first = true;
	return self;
}

static PyResultIterator* PyResultIterator_iter(PyResultIterator *self) {
	Py_INCREF(self);
	return self;
}

static PyResult* PyResultIterator_next(PyResultIterator *self) {
	if (!self->first) {
		int success = self->ri->Next(self->level);
		if (!success) {
			PyErr_SetNone(PyExc_StopIteration);
			return NULL;
		}
	} else {
		self->first = false;
	}
	const char *text = self->ri->GetUTF8Text(self->level);
	float confidence = self->ri->Confidence(self->level);
	PyBoundingBox *bounding_box = PyObject_New(PyBoundingBox, &PyBoundingBox_Type);
	self->ri->BoundingBox(self->level, &bounding_box->left, &bounding_box->top, &bounding_box->right, &bounding_box->bottom);
	PyObject *py_text = PyUnicode_FromString(text);
	delete[] text;
	text = NULL;
	PyObject *args = Py_BuildValue("OOf", py_text, bounding_box, confidence);
	PyResult *result = (PyResult *)PyObject_CallObject((PyObject *)&PyResult_Type, args);
	Py_CLEAR(args);
	return result;
}

static void PyResultIterator_dealloc(PyResultIterator *self) {
	if (self->ri) {
		delete(self->ri);
		self->ri = NULL;
	}
	PyObject_Del(self);
}

/* Tesseract methods */

static PyTesseract* PyTesseract_new(PyTypeObject *type, PyObject* /* args */, PyObject* /* kwargs */) {
	PyTesseract *self = PyObject_New(PyTesseract, &PyTesseract_Type);
	if (self == NULL) {
		return NULL;
	}
	self->tess = new tesseract::TessBaseAPI();
	self->image = NULL;

	// TessOcrEngineMode
	PyDict_SetItemString(type->tp_dict, "OEM_TESSERACT_ONLY", PyInt_FromLong(tesseract::OEM_TESSERACT_ONLY));
	PyDict_SetItemString(type->tp_dict, "OEM_CUBE_ONLY", PyInt_FromLong(tesseract::OEM_CUBE_ONLY));
	PyDict_SetItemString(type->tp_dict, "OEM_TESSERACT_CUBE_COMBINED", PyInt_FromLong(tesseract::OEM_TESSERACT_CUBE_COMBINED));
	PyDict_SetItemString(type->tp_dict, "OEM_DEFAULT", PyInt_FromLong(tesseract::OEM_DEFAULT));

	// TessPageSegMode
	PyDict_SetItemString(type->tp_dict, "PSM_OSD_ONLY", PyInt_FromLong(tesseract::PSM_OSD_ONLY));
	PyDict_SetItemString(type->tp_dict, "PSM_AUTO_OSD", PyInt_FromLong(tesseract::PSM_AUTO_OSD));
	PyDict_SetItemString(type->tp_dict, "PSM_AUTO_ONLY", PyInt_FromLong(tesseract::PSM_AUTO_ONLY));
	PyDict_SetItemString(type->tp_dict, "PSM_AUTO", PyInt_FromLong(tesseract::PSM_AUTO));
	PyDict_SetItemString(type->tp_dict, "PSM_SINGLE_COLUMN", PyInt_FromLong(tesseract::PSM_SINGLE_COLUMN));
	PyDict_SetItemString(type->tp_dict, "PSM_SINGLE_BLOCK_VERT_TEXT", PyInt_FromLong(tesseract::PSM_SINGLE_BLOCK_VERT_TEXT));
	PyDict_SetItemString(type->tp_dict, "PSM_SINGLE_BLOCK", PyInt_FromLong(tesseract::PSM_SINGLE_BLOCK));
	PyDict_SetItemString(type->tp_dict, "PSM_SINGLE_LINE", PyInt_FromLong(tesseract::PSM_SINGLE_LINE));
	PyDict_SetItemString(type->tp_dict, "PSM_SINGLE_WORD", PyInt_FromLong(tesseract::PSM_SINGLE_WORD));
	PyDict_SetItemString(type->tp_dict, "PSM_CIRCLE_WORD", PyInt_FromLong(tesseract::PSM_CIRCLE_WORD));
	PyDict_SetItemString(type->tp_dict, "PSM_SINGLE_CHAR", PyInt_FromLong(tesseract::PSM_SINGLE_CHAR));
	PyDict_SetItemString(type->tp_dict, "PSM_COUNT", PyInt_FromLong(tesseract::PSM_COUNT));

	// PageIteratorLevel
	PyDict_SetItemString(type->tp_dict, "RIL_BLOCK", PyInt_FromLong(tesseract::RIL_BLOCK));
	PyDict_SetItemString(type->tp_dict, "RIL_PARA", PyInt_FromLong(tesseract::RIL_PARA));
	PyDict_SetItemString(type->tp_dict, "RIL_TEXTLINE", PyInt_FromLong(tesseract::RIL_TEXTLINE));
	PyDict_SetItemString(type->tp_dict, "RIL_WORD", PyInt_FromLong(tesseract::RIL_WORD));
	PyDict_SetItemString(type->tp_dict, "RIL_SYMBOL", PyInt_FromLong(tesseract::RIL_SYMBOL));
	return self;
}

static void PyTesseract_dealloc(PyTesseract *self) {
	if (self->tess) {
		delete(self->tess);
		self->tess = NULL;
	}
	if (self->image) {
		Py_CLEAR(self->image);
	}
	PyObject_Del(self);
}

static int PyTesseract_init(PyTesseract *self, PyObject *args, PyObject *kwargs) {
	char *datapath = NULL;
	char *language = NULL;
	tesseract::OcrEngineMode oem = tesseract::OEM_TESSERACT_ONLY;

	static const char *kwlist[] = { "data_path", "language", "oem", NULL };
	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "s|si", (char **)kwlist, &datapath, &language, &oem)) {
		return -1;
	}
	int result = self->tess->Init(datapath, language, oem);
	if (result) {
		PyErr_SetString(PyExc_EnvironmentError, "Error initializing Tesseract");
	}
	return result;
}

static PyObject* PyTesseract_clear(PyTesseract *self) {
	self->tess->Clear();
	if (self->image) {
		Py_CLEAR(self->image);
	}
	Py_INCREF(Py_None);
	return Py_None;
}

static int PyTesseract_setattr(PyTesseract *self, PyObject *attr, PyObject *py_value) {
	// attribute name must be a string, but value will be converted with str()
	char *name = PyString_AsString(attr);
	if (!name) {
		PyErr_SetString(PyExc_TypeError, "Attribute name must be a string");
		return -1;
	}

	PyObject *py_value_str = PyObject_Str(py_value);
	if (!py_value_str) {
		PyErr_SetString(PyExc_TypeError, "Could not get string value of attribute");
		return -1;
	}

	char *value = PyString_AsString(py_value_str);
	bool result = self->tess->SetVariable(name, value);
	Py_CLEAR(py_value_str);
	if (!result) {
		PyErr_SetObject(PyExc_AttributeError, attr);
		return -1;
	}
	return 0;
}

static PyObject* PyTesseract_getattr(PyTesseract *self, PyObject *attr) {
	PyObject *existing = PyObject_GenericGetAttr((PyObject *)self, attr);
	if (existing) {
		return existing;
	}
	PyErr_Clear();
	// attribute name must be a string
	char *name = PyString_AsString(attr);
	if (!name) {
		PyErr_SetString(PyExc_TypeError, "Attribute name is not a string");
		return NULL;
	}

	STRING value;
	bool result = self->tess->GetVariableAsString(name, &value);
	if (!result) {
		PyErr_SetObject(PyExc_AttributeError, attr);
		return NULL;
	}
	return PyString_FromString(value.string());
}

static PyObject* PyTesseract_set_image(PyTesseract *self, PyObject *array) {
	if (!PyArray_Check(array)) {
		PyErr_SetString(PyExc_TypeError, "Image must be a NumPy array");
		return NULL;
	}

	PyArrayObject *np_array = (PyArrayObject *)array;
	npy_intp *shape = PyArray_DIMS(np_array);
	int dimension_count = PyArray_NDIM(np_array);
	int channels = 0;
	switch (dimension_count) {
		case 2:
			channels = 1;
			break;
		case 3:
			channels = (int)shape[2];
			break;
		default:
			PyErr_SetString(PyExc_TypeError, "Invalid array format");
			return NULL;
	}
	int bytes_per_channel = 0;
	switch (PyArray_TYPE(np_array)) {
		case NPY_BYTE:
		case NPY_UBYTE:
			bytes_per_channel = 1;
			break;
		case NPY_SHORT:
		case NPY_USHORT:
			bytes_per_channel = 2;
			break;
		case NPY_FLOAT:
			bytes_per_channel = 4;
			break;
		case NPY_DOUBLE:
			bytes_per_channel = 8;
			break;
		default:
			PyErr_SetString(PyExc_TypeError, "Invalid array format");
			return NULL;
	}

	int rows = (int)shape[0];
	int cols = (int)shape[1];

	Py_INCREF(array);
	self->image = array;
	int bytes_per_pixel = bytes_per_channel * channels;

	self->tess->SetImage((unsigned char *)PyArray_BYTES(np_array), cols, rows, bytes_per_pixel, bytes_per_pixel * cols);

	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject* PyTesseract_set_rectangle(PyTesseract *self, PyObject *args, PyObject *kwargs) {
	int top = -1;
	int left = -1;
	int width = -1;
	int height = 1;
	static const char *kwlist[] = { "top", "left", "width", "height", NULL };
	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "iiii:set_rectangle", (char **)kwlist, &top, &left, &width, &height)) {
		return NULL;
	}
	self->tess->SetRectangle(left, top, width, height);

	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject* PyTesseract_recognize(PyTesseract *self) {
	int error = self->tess->Recognize(NULL);
	if (error) {
		Py_INCREF(Py_False);
		return Py_False;
	}
	Py_INCREF(Py_True);
	return Py_True;
}

static PyObject* PyTesseract_get_utf8_text(PyTesseract *self) {
	char *text = self->tess->GetUTF8Text();
	PyObject *unicode = PyUnicode_FromString(text);
	delete(text);
	text = NULL;
	return unicode;
}

static PyObject* PyTesseract_mean_text_conf(PyTesseract *self) {
	int confidence = self->tess->MeanTextConf();
	return PyInt_FromLong(confidence);
}

/** Helper function for following iterator requests */
static PyResultIterator *PyTesseract_iterator(PyTesseract *self) {
	tesseract::ResultIterator *ri = self->tess->GetIterator();
	PyResultIterator *iterator = (PyResultIterator *)PyObject_CallObject((PyObject *)&PyResultIterator_Type, (PyObject *)NULL);
	iterator->ri = ri;
	return iterator;
}

static PyResultIterator* PyTesseract_symbols(PyTesseract *self) {
	PyResultIterator *iterator = PyTesseract_iterator(self);
	iterator->level = tesseract::RIL_SYMBOL;
	return iterator;
}

static PyResultIterator* PyTesseract_words(PyTesseract *self) {
	PyResultIterator *iterator = PyTesseract_iterator(self);
	iterator->level = tesseract::RIL_WORD;
	return iterator;
}

static PyResultIterator* PyTesseract_text_lines(PyTesseract *self) {
	PyResultIterator *iterator = PyTesseract_iterator(self);
	iterator->level = tesseract::RIL_TEXTLINE;
	return iterator;
}

static PyResultIterator* PyTesseract_paragraphs(PyTesseract *self) {
	PyResultIterator *iterator = PyTesseract_iterator(self);
	iterator->level = tesseract::RIL_PARA;
	return iterator;
}

static PyResultIterator* PyTesseract_blocks(PyTesseract *self) {
	PyResultIterator *iterator = PyTesseract_iterator(self);
	iterator->level = tesseract::RIL_BLOCK;
	return iterator;
}

static PyMethodDef TesserPyMethods[] = {
	{ NULL, NULL } // sentinel
};

PyMODINIT_FUNC inittesserpy(void) {
	PyBoundingBox_Type.tp_new = PyType_GenericNew;
	if (PyType_Ready(&PyBoundingBox_Type) < 0) {
		return;
	}

	PyResult_Type.tp_new = PyType_GenericNew;
	if (PyType_Ready(&PyResult_Type) < 0) {
		return;
	}

	if (PyType_Ready(&PyResultIterator_Type) < 0) {
		return;
	}

	if (PyType_Ready(&PyTesseract_Type) < 0) {
		return;
	}

	PyObject *module = Py_InitModule("tesserpy", TesserPyMethods);
	if (module == NULL) {
		return;
	}

	import_array();

	Py_INCREF(&PyBoundingBox_Type);
	PyModule_AddObject(module, "BoundingBox", (PyObject *)&PyBoundingBox_Type);

	Py_INCREF(&PyResult_Type);
	PyModule_AddObject(module, "Result", (PyObject *)&PyResult_Type);

	Py_INCREF(&PyResultIterator_Type);
	PyModule_AddObject(module, "ResultIterator", (PyObject *)&PyResultIterator_Type);

	Py_INCREF(&PyTesseract_Type);
	PyModule_AddObject(module, "Tesseract", (PyObject *)&PyTesseract_Type);
}
