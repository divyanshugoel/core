// Copyright 2022 Divyanshu Goel.
#pragma once

////////////////////////////////////////////////////////////////////////////////
// File/Folder Utilities
namespace fms
{
// Check if the file/folder exists.

// bool DirExists();
// bool copyDir(, duplicateBehavior, errorhandler);
// bool mkdir(path, errorhandler);
// bool traverse()
// bool copyFile(, duplicateBehavior, errorhandler);
// bool moveFile(, duplicateBehavior, errorhandler);
// bool removeFile(, duplicateBehavior, errorhandler);
// bool generateUniqueName(, duplicateBehavior, errorhandler);
// bool LengthExceedsMax()

// ////////////////////////////////////////
// // Utility functions to read the entire content from files/streams
// //	- All throw exception on failure
// ////////////////////////////////////////

// // Reads all binary or text data from the given stream
// std::string ReadStreamContents(std::istream& stream);
// // Reads all text data from the given stream
// std::string ReadTextStreamContents(std::istream& stream);

// // Reads all binary data from the given file
// std::string ReadBinaryFileContents(const std::string& filePath);
// // Reads all text data from the given file
// std::string ReadTextFileContents(const std::string& filePath);

// ////////////////////////////////////////
// // Utility functions to write the entire content to files/streams
// //  - All throw fmsException on failure
// ////////////////////////////////////////

// // Writes all binary or text data to the given stream
// void WriteStreamContents(std::ostream& stream, const std::string& content);
// // Writes text data to the given stream (after converting to std::string)
// void WriteStreamContents(std::ostream& stream, const std::string& content);

// // Writes all binary data to the given file
// void WriteBinaryFileContents(
// const std::string& filePath, const std::string& content,
// fmsFileOutputStreamBase::Append append = fmsFileOutputStreamBase::Append(false),
// fmsFileOutputStreamBase::SafeWrite safeWrite = fmsFileOutputStreamBase::SafeWrite(true));
// // Writes all text data to the given file
// void WriteTextFileContents(
// const QString& filePath, const QString& content,
// fmsFileOutputStreamBase::Append append = fmsFileOutputStreamBase::Append(false),
// fmsFileOutputStreamBase::SafeWrite safeWrite = fmsFileOutputStreamBase::SafeWrite(true));

} // namespace fms
